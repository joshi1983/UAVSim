#ifndef BITMAP_GENERATION_LISTENER_HEADER_INCLUDED
#define BITMAP_GENERATION_LISTENER_HEADER_INCLUDED
#include <gdiplus.h>

class BitmapGenerationListener
{
	public:
		virtual void handle(Gdiplus::Bitmap * bitmap) = 0;
};

#endif
