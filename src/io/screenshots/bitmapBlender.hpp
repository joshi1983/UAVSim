#ifndef BITMAP_BLENDER_HEADER_INCLUDED
#define BITMAP_BLENDER_HEADER_INCLUDED
#include <windows.h>
#include <gdiplus.h>
#include <vector>

Gdiplus::Bitmap* motionBlend(const std::vector<Gdiplus::Bitmap *> &bitmaps);
void addFrame(Gdiplus::Bitmap * bitmap);
void saveMotionBlurredFrameTo(const char * filename);
void saveMotionBlurredFrameTo(const wchar_t * filename);

#endif
