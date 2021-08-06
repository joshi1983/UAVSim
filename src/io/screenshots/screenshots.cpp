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
#include <thread>
#include <chrono>
#include "../../lib/SharedQueue/SharedQueue.cpp"
#include "../../lib/rapidjson/pointer.h"
#include "../../lib/rapidjson/document.h"
#include "../stringUtils.hpp"
#include "../config/UAVSimConfig.hpp"
#include "../Files.hpp"
#include "bitmapBlender.hpp"
using namespace std;
using namespace rapidjson;

void saverThreadRun();
thread th(&saverThreadRun);
const CLSID pngEncoderClsId = { 0x557cf406, 0x1a04, 0x11d3,{ 0x9a,0x73,0x00,0x00,0xf8,0x1e,0xf3,0x2e } };

// Create a string with last error message
std::string GetLastErrorStdStr()
{
  DWORD error = GetLastError();
  if (error)
  {
    LPVOID lpMsgBuf;
    DWORD bufLen = FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        error,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );
    if (bufLen)
    {
      LPCSTR lpMsgStr = (LPCSTR)lpMsgBuf;
      std::string result(lpMsgStr, lpMsgStr+bufLen);

      LocalFree(lpMsgBuf);

      return result;
    }
  }
  return std::string();
}

class ScreenShotSaveTask
{
    public:
        ScreenShotSaveTask(Gdiplus::Bitmap*, const wstring &filename);
        Gdiplus::Bitmap* bitmap;
        wstring filename;
        ~ScreenShotSaveTask();
};

ScreenShotSaveTask::ScreenShotSaveTask(Gdiplus::Bitmap* bitmap, const wstring &filename): bitmap(bitmap), filename(filename)
{

}

ScreenShotSaveTask::~ScreenShotSaveTask()
{
    delete bitmap;
}

SharedQueue<ScreenShotSaveTask *> screenshotQueue;
HWND screenshotWindow;

void storeHWND(int windowid, const char * title)
{
    HDC hdc = wglGetCurrentDC();
    screenshotWindow = WindowFromDC(hdc);
    //screenshotWindow = GetForegroundWindow();
}

bool canSaveScreenshot()
{
    return screenshotQueue.size() < 10;
}

void saverThreadRun()
{
    while (true)
    {
        if (!screenshotQueue.empty())
        {
            while (!screenshotQueue.empty())
            {
                ScreenShotSaveTask* task = screenshotQueue.front();
                screenshotQueue.pop_front();

                Gdiplus::Status result = task->bitmap->Save(task->filename.c_str(), &pngEncoderClsId, NULL);
                if (result != Gdiplus::Status::Ok)
                {
                    if (result == Gdiplus::Status::Win32Error)
                    {
                        cerr << "Win32Error" << endl;
                        cerr << GetLastErrorStdStr() << endl;
                    }
                    else if (result == Gdiplus::Status::WrongState)
                        cerr << "WrongState" << endl;
                    else if (result == Gdiplus::Status::NotImplemented)
                        cerr << "NotImplemented" << endl;
                    cerr << "Saving failed with status: " << result << endl;
                }
                delete task;
            }
        }
        else {
            // sleep for 10 miliseconds.
            this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

void switchedMotionBlurGroup(const string& filename)
{
    saveMotionBlurredFrameTo(filename.c_str());
}

void saveScreenshot(const char * filename)
{
    wchar_t convertedFilename[256];
    convertToWCharString(filename, convertedFilename);
    saveScreenshot(convertedFilename);
}

Gdiplus::Bitmap * getScreenshotBitmap()
{
    Gdiplus::Bitmap *image = nullptr;
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
    if (!bRet)
        cerr << "BitBlt failed." << endl;
    else
    {
        image = new Gdiplus::Bitmap(hBitmap, NULL);
    }

    // clean-up
    SelectObject(hDC, old_obj);
    DeleteDC(hDC);
    ReleaseDC(NULL, hWindow);
    DeleteObject(hBitmap);
    return image;
}

void saveScreenshot(const wchar_t * filename)
{
    Gdiplus::Bitmap *image = getScreenshotBitmap();
    if (image != nullptr)
    {
        addFrame(image);
    }
}

void getScreenshotPNGRawData(std::vector<unsigned char>& result)
{
    Gdiplus::Bitmap *image = getScreenshotBitmap();
    IStream* istream = nullptr;
    HGLOBAL hg=NULL;
    if (CreateStreamOnHGlobal(hg, FALSE, (LPSTREAM*)&istream)!=S_OK)
        cerr << "error on creating an empty IStream" << endl;

    image->Save(istream, &pngEncoderClsId, nullptr);
    STATSTG stats;
    istream->Stat(&stats,STATFLAG_DEFAULT);
    int buffsize=(int)stats.cbSize.QuadPart;
    char *pBuff = new char[buffsize];
    ULONG ulBytesRead;
    LARGE_INTEGER lg;
    lg.QuadPart = 0;
    istream->Seek(lg, STREAM_SEEK_SET, NULL);

     //Read the stream to pBuff
    if (istream->Read(pBuff, buffsize, &ulBytesRead)!=S_OK)
        cerr << "error on saving IStream to buffer";


    //release will automatically free the memory allocated in CreateStreamOnHGlobal
    istream->Release();
    for (int i = 0; i < buffsize; i++) {
        result.push_back(pBuff[i]);
    }

    delete[] pBuff;

    delete image;
}

void updateResolutionFromConfig()
{
    int w = UAVSimConfig::config.getDefaultedInt("/resolution/width", 640);
    int h = UAVSimConfig::config.getDefaultedInt("/resolution/height", 480);
    glutReshapeWindow(w, h);
}
