#include "AnimationSettings.hpp"
#include "../../io/config/UAVSimConfig.hpp"
using namespace std;

int cachedBlurSamplesPerFrame = -1;

int getCSVRowsPerFrame()
{
    UAVSimConfig& c = UAVSimConfig::config;
	int csvRowsPerFrame = c.getDefaultedInt("/csv/blurFrameCount", 1);
	if (isBlurringBetweenRows())
        csvRowsPerFrame = 1;
	return csvRowsPerFrame;
}

string getFrameOutputDirectory()
{
    UAVSimConfig& c = UAVSimConfig::config;
    string outputPath = c.getDefaultedString("/frameOutputDirectory", "outputs/frames/");
    if (outputPath[outputPath.length() - 1] != '/')
        outputPath += '/';
	return outputPath;
}

unsigned int getBlurSamplesPerFrame()
{
	if (cachedBlurSamplesPerFrame <= 0)
	{
		UAVSimConfig &config = UAVSimConfig::config;
		cachedBlurSamplesPerFrame = config.getDefaultedInt("/csv/blurFrameCount", 1);
		if (cachedBlurSamplesPerFrame <= 0)
			cachedBlurSamplesPerFrame = 1; // sanitize to 1.  It must be at least 1.
	}
	return cachedBlurSamplesPerFrame;
}

unsigned short getFPS()
{
	UAVSimConfig & config = UAVSimConfig::config;
	return config.getDefaultedInt("/ffmpeg/fps", 30);
}

bool isBlurringBetweenRows()
{
	UAVSimConfig &config = UAVSimConfig::config;
    return config.getDefaultedBool("/csv/blurBetweenRows", true);
}

bool isSavingFrames()
{
	return UAVSimConfig::config.getDefaultedBool("/csv/isSavingFrames", true);
}

void getOutputResolution(int & width, int & height)
{
	width = UAVSimConfig::config.getDefaultedInt("/resolution/width", 640);
	height = UAVSimConfig::config.getDefaultedInt("/resolution/height", 480);
}