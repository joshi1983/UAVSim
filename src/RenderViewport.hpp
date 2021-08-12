#ifndef RENDER_VIEWPORT_HEADER_INCLUDED
#define RENDER_VIEWPORT_HEADER_INCLUDED

class RenderViewport
{
	public:
		RenderViewport();
		RenderViewport(double widthRatio, double heightRatio, double leftRatio, double topRatio);
		double widthRatio, heightRatio; // The values should be in the range: 0 < x <= 1.
		double leftRatio, topRatio; // The values should be in the range: 0 <= x < 1.
};

#endif
