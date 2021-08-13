#include "Resolution.hpp"
#include "wtypes.h"
#include "AnimationSettings.hpp"
using namespace std;

// Adapted from an answer at:
// https://stackoverflow.com/questions/8690619/how-to-get-screen-resolution-in-c
void getScreenResolution(int& horizontal, int& vertical)
{
   RECT desktop;
   // Get a handle to the desktop window
   const HWND hDesktop = GetDesktopWindow();
   // Get the size of screen to the variable desktop
   GetWindowRect(hDesktop, &desktop);
   // The top left corner will have coordinates (0,0)
   // and the bottom right corner will have coordinates
   // (horizontal, vertical)
   horizontal = desktop.right;
   vertical = desktop.bottom;
}

void getMaximumWindowResolution(int& horizontal, int& vertical)
{
	getScreenResolution(horizontal, vertical);
	horizontal -= 50;
	vertical -= 100;
}

void getSuggestedWindowResolution(int& horizontal, int& vertical)
{
	int numColumns, numRows;
	getSuggestedWindowGrid(numColumns, numRows);
	int outputWidth, outputHeight;
	getOutputResolution(outputWidth, outputHeight);
	horizontal = outputWidth / numColumns;
	vertical = outputHeight / numRows;
}

void getSuggestedWindowGrid(int & numColumns, int & numRows)
{
	int outputWidth, outputHeight;
	getOutputResolution(outputWidth, outputHeight);
	int maxWindowWidth, maxWindowHeight;
	getMaximumWindowResolution(maxWindowWidth, maxWindowHeight);
	if (outputWidth > maxWindowWidth)
		numColumns = outputWidth / maxWindowWidth;
	else
		numColumns = 1;
	if (outputHeight > maxWindowHeight)
		numRows = outputHeight / maxWindowHeight;
	else
		numRows = 1;
}
