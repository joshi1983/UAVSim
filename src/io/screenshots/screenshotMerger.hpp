#ifndef SCREENSHOT_MERGER_HEADER_INCLUDED
#define SCREENSHOT_MERGER_HEADER_INCLUDED
#include <windows.h>
#include <gdiplus.h>
#include <vector>

class ScreenshotMergePiece
{
	public:
		ScreenshotMergePiece(Gdiplus::Bitmap* from, int left, int top);
		int left, top;
		Gdiplus::Bitmap* from;
};

void draw(std::vector<ScreenshotMergePiece>, Gdiplus::Bitmap& destination);

#endif