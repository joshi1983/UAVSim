#include "screenshotMerger.hpp"
using namespace std;

ScreenshotMergePiece::ScreenshotMergePiece(Gdiplus::Bitmap* from, int left, int top): left(left), top(top), from(from)
{

}

void draw(Gdiplus::Bitmap* from, int left, int top, Gdiplus::Bitmap& destination)
{
    Gdiplus::Graphics *mem = Gdiplus::Graphics::FromImage(&destination);
    mem->DrawImage(from, left, top, 0, 0, from->GetWidth(), from->GetHeight(), Gdiplus::UnitPixel);
}

void draw(std::vector<ScreenshotMergePiece> pieces, Gdiplus::Bitmap& destination)
{
	for (ScreenshotMergePiece& piece: pieces)
	{
		draw(piece.from, piece.left, piece.top, destination);
	}
}
