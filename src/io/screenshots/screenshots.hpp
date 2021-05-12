#ifndef SCREENSHOTS_HEADER_INCLUDED
#define SCREENSHOTS_HEADER_INCLUDED

void storeHWND(int windowid, const char * title);
void updateResolutionFromConfig();
void saveScreenshot(const wchar_t * filename);
void saveScreenshot(const char * filename);
void saveScreenshot(unsigned int frameIndex);

#endif
