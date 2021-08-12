#include "RenderViewport.hpp"
using namespace std;

RenderViewport::RenderViewport(): widthRatio(1), heightRatio(1), leftRatio(0), topRatio(0)
{

}

RenderViewport::RenderViewport(double widthRatio, double heightRatio, double leftRatio, double topRatio):
	widthRatio(widthRatio), heightRatio(heightRatio), leftRatio(leftRatio), topRatio(topRatio)
{

}
