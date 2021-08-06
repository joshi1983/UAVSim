#include "bitmapBlender.hpp"
#include <gdiplus.h>
#include <cmath>
#include <thread>
#include "../stringUtils.hpp"
#include "../../lib/SharedQueue/SharedQueue.cpp"
#include <iostream>
using namespace std;

SharedQueue<Gdiplus::Bitmap *> screenshotMotionQueue;

void addFrame(Gdiplus::Bitmap * bitmap)
{
    screenshotMotionQueue.push_back(bitmap);
}

void saveMotionBlurredFrameTo(const char * filename)
{
    wchar_t convertedFilename[256];
    convertToWCharString(filename, convertedFilename);
    saveMotionBlurredFrameTo(convertedFilename);
}

void saveMotionBlurredFrameTo(const wchar_t * filename)
{
    vector<Gdiplus::Bitmap*> bitmaps;
    while (!screenshotMotionQueue.empty())
    {
        bitmaps.push_back(screenshotMotionQueue.front());
        screenshotMotionQueue.pop_front();
    }

    Gdiplus::Bitmap* result = motionBlend(bitmaps);
    // save to file.
    const CLSID pngEncoderClsId = { 0x557cf406, 0x1a04, 0x11d3,{ 0x9a,0x73,0x00,0x00,0xf8,0x1e,0xf3,0x2e } };
    result->Save(filename, &pngEncoderClsId, NULL);

    for (const Gdiplus::Bitmap * bitmap: bitmaps)
    {
        delete bitmap;
    }
    delete result;
}

// Finds the maximum width and height for all the specified bitmaps.
void maxDimensions(const vector<Gdiplus::Bitmap *> &bitmaps, unsigned int& width, unsigned int&height)
{
    width = 0;
    height = 0;
    for (Gdiplus::Bitmap * bitmap: bitmaps)
    {
        unsigned int w = bitmap->GetWidth();
        unsigned int h = bitmap->GetHeight();
        width = max(w, width);
        height = max(h, height);
    }
}

// Finds appropriate blending ratios for each frame.
void getBlendRatios(const vector<Gdiplus::Bitmap *> &bitmaps, double* blendRatios)
{
    double halfSize = bitmaps.size() * 0.5;
    double r = bitmaps.size() * 0.55;
    double rSquared = r * r;
    double total = 0;
    for (unsigned int i = 0; i < bitmaps.size(); i++)
    {
        double di = i - halfSize;
        blendRatios[i] = sqrt(rSquared - di * di);
        total += blendRatios[i];
    }
    double scaleFactor = 1.0 / total;
    for (unsigned int i = 0; i < bitmaps.size(); i++)
        blendRatios[i] *= scaleFactor;
}

Gdiplus::Bitmap* motionBlend(const vector<Gdiplus::Bitmap *> &bitmaps)
{
    unsigned int w, h;
    double* blendRatios = new double[bitmaps.size()];
    maxDimensions(bitmaps, w, h);
    getBlendRatios(bitmaps, blendRatios);
    double *rgbValues = new double[w * h * 3];
    memset(rgbValues,0,w * h * 3 * sizeof(double));
    int i=0;
    for (Gdiplus::Bitmap * bitmap: bitmaps)
    {
        double blendRatio = blendRatios[i++];
        Gdiplus::BitmapData bitmapData;
        unsigned int localW = bitmap->GetWidth(), localH = bitmap->GetHeight();
        Gdiplus::Rect rect(0, 0, localW, localH);
        bitmap->LockBits(&rect, Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, &bitmapData);
        unsigned char *pSourcePixels = (unsigned char*)bitmapData.Scan0;

        for (unsigned int y = 0; y < localH; y++)
        {
            for (unsigned int x = 0; x < localW; x++)
            {
                unsigned int sourceIndex = x*4;
                unsigned int destIndex = (x + y * w) * 3;
                rgbValues[destIndex] += pSourcePixels[sourceIndex] * blendRatio;
                rgbValues[destIndex + 1] += pSourcePixels[sourceIndex + 1] * blendRatio;
                rgbValues[destIndex + 2] += pSourcePixels[sourceIndex + 2] * blendRatio;
            }

            // advance row pointers
            pSourcePixels += bitmapData.Stride;
        }
        bitmap->UnlockBits(&bitmapData);
    }

    Gdiplus::Bitmap * result = new Gdiplus::Bitmap(w, h, PixelFormat24bppRGB);
    // copy rgbValues to result.
    {
        Gdiplus::Rect rect(0, 0, w, h);
        Gdiplus::BitmapData bitmapData;
        result->LockBits(&rect, Gdiplus::ImageLockModeRead, PixelFormat24bppRGB, &bitmapData);
        unsigned char *pDestPixels = (unsigned char*)bitmapData.Scan0;
        for (unsigned int y = 0; y < h; y++)
        {
            for (unsigned int x = 0; x < w; x++)
            {
                unsigned int destIndex = x*3;
                unsigned int sourceIndex = (x + y * w) * 3;
                pDestPixels[destIndex] = (unsigned char)(min(255.0, rgbValues[sourceIndex]));
                pDestPixels[destIndex + 1] = (unsigned char)(min(255.0, rgbValues[sourceIndex + 1]));
                pDestPixels[destIndex + 2] = (unsigned char)(min(255.0, rgbValues[sourceIndex + 2]));
            }

            // advance row pointers
            pDestPixels += bitmapData.Stride;
        }
        result->UnlockBits(&bitmapData);
    }
    delete [] rgbValues;

    return result;
}
