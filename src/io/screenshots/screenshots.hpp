#ifndef SCREENSHOTS_HEADER_INCLUDED
#define SCREENSHOTS_HEADER_INCLUDED
#include <string>

void storeHWND(int windowid, const char * title);
void updateResolutionFromConfig();
void saveScreenshot(const wchar_t * filename);
void saveScreenshot(const char * filename);
void switchedMotionBlurGroup(const std::string& filename);
bool canSaveScreenshot();

#endif
