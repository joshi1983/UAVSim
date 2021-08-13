#ifndef ANIMATION_SETTINGS_HEADER_INCLUDED
#define ANIMATION_SETTINGS_HEADER_INCLUDED
#include <string>

unsigned int getBlurSamplesPerFrame();
unsigned short getFPS();
bool isBlurringBetweenRows();
std::string getFrameOutputDirectory();
int getCSVRowsPerFrame();
bool isSavingFrames();
void getOutputResolution(int & width, int & height);

#endif
