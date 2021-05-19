#include "screenshots.hpp"
#include <gdiplus.h>
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include "../../lib/rapidjson/pointer.h"
#include "../../lib/rapidjson/document.h"
#include "../stringUtils.hpp"
#include "../config/Config.hpp"
#include "../Files.hpp"
using namespace std;
using namespace rapidjson;

HWND screenshotWindow;

void storeHWND(int windowid, const char * title)
{
    HDC hdc = wglGetCurrentDC();
    screenshotWindow = WindowFromDC(hdc);
    //screenshotWindow = GetForegroundWindow();
}

void saveScreenshot(const char * filename)
{
    wchar_t convertedFilename[256];
    convertToWCharString(filename, convertedFilename);
    saveScreenshot(convertedFilename);
}

void saveScreenshot(const wchar_t * filename)
{
	RECT r;
    int x1=0, y1=0, x2=0, y2=0, w=0, h=0;
	GetClientRect(screenshotWindow, &r);

    x1 = r.left;
    y1 = r.top;
    x2 = r.right;
    y2 = r.bottom;

    // width and height
    w = x2 - x1;
    h = y2 - y1;

    // copy window to bitmap
    HDC     hWindow = (HDC) GetDC(screenshotWindow);
    HDC     hDC = CreateCompatibleDC(hWindow);
    HBITMAP hBitmap = CreateCompatibleBitmap(hWindow, w, h);
    HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
    BOOL    bRet = BitBlt(hDC, 0, 0, w, h, hWindow, x1, y1, SRCCOPY);

    Gdiplus::Bitmap image(hBitmap, NULL);
    const CLSID pngEncoderClsId = { 0x557cf406, 0x1a04, 0x11d3,{ 0x9a,0x73,0x00,0x00,0xf8,0x1e,0xf3,0x2e } };

    image.Save(filename, &pngEncoderClsId, NULL);

    // clean-up
    SelectObject(hDC, old_obj);
    DeleteDC(hDC);
    ReleaseDC(NULL, hWindow);
    DeleteObject(hBitmap);
}

void updateResolutionFromConfig()
{
    Value* csv =  Pointer("/csv").Get(UAVSimConfig::config.doc);
    Value* res =  Pointer("/resolution").Get(UAVSimConfig::config.doc);
    Value* width =  Pointer("/resolution/width").Get(UAVSimConfig::config.doc);
    Value* height =  Pointer("/resolution/height").Get(UAVSimConfig::config.doc);
    if (width != nullptr && height != nullptr && width->IsInt() && height->IsInt())
    {
        int w = width->GetInt();
        int h = height->GetInt();
        cout << "w = " << w << ", h = " << h << endl;
        glutReshapeWindow(w, h);
    }
    else {
        cout << "csv is null: " << (csv == nullptr) << endl;
        cout << "res is null: " << (res == nullptr) << endl;
        cout << "width is null: " << (width == nullptr) << endl;
        cout << "height is null: " << (height == nullptr) << endl;
        cout << "width and height not found in config. width = " << width << ", height = " << height << endl;
    }
}
