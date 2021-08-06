#ifndef SCREENSHOTS_HEADER_INCLUDED
#define SCREENSHOTS_HEADER_INCLUDED
#include <string>
#include <vector>
#include <gdiplus.h>

Gdiplus::Bitmap * getScreenshotBitmap();
void storeHWND(int windowid, const char * title);
void updateResolutionFromConfig();
void saveScreenshot(const wchar_t * filename);
void saveScreenshot(const char * filename);
void getScreenshotPNGRawData(std::vector<unsigned char>& result);
void switchedMotionBlurGroup(const std::string& filename);
bool canSaveScreenshot();

#endif
