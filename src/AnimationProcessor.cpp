#include "AnimationProcessor.hpp"
#include "io/screenshots/screenshots.hpp"
#include "io/config/Config.hpp"
#include "lib/rapidjson/pointer.h"
#include "io/Files.hpp"
#include <cstdio>
#include <string>
#include <iostream>
using namespace std;
using namespace rapidjson;

string outputPath;
bool blurBetweenRows;

AnimationProcessor::AnimationProcessor(Animation* animation,
	AnimationState & animationState):
	animation(animation), animationState(animationState), frameIndex(0)
{
    UAVSimConfig& c = UAVSimConfig::config;
    blurFrameCount = c.getDefaultedInt("/csv/blurFrameCount", 1);
    outputPath = c.getDefaultedString("/frameOutputDirectory", "outputs/frames/");
    if (outputPath[outputPath.length() - 1] != '/')
        outputPath += '/';

    blurBetweenRows = c.getDefaultedBool("/csv/blurBetweenRows", false);
}

void AnimationProcessor::deleteFrameAfterAnimation() const
{
    double maxT = animation->getMaxT();
    int maxFrameIndex = (int)(maxT + 0.01);
    string filename = AnimationProcessor::getFileName(maxFrameIndex, 1);
    remove(filename.c_str()); // if it doesn't exist, this will do nothing and that is ok.
}

std::string AnimationProcessor::getFileName(int frameIndex, int blurFrameCount)
{
	char filenameBuffer[256];
	char filenameBuffer2[256];
	if (blurFrameCount == 1)
        sprintf(filenameBuffer, "frame_%08d.png", frameIndex);
    else
        sprintf(filenameBuffer, "frame_%08d_%08d.png", frameIndex / blurFrameCount, frameIndex % blurFrameCount);

    sprintf(filenameBuffer2, "%s%s", outputPath.c_str(), filenameBuffer);
	return getAbsolutePathForFilename(filenameBuffer2);
}

string AnimationProcessor::getFileName() const
{
    return getFileName(frameIndex, blurFrameCount);
}

string AnimationProcessor::getBlurGroupFileName() const
{
	char filenameBuffer[256];
	char filenameBuffer2[256];
    sprintf(filenameBuffer, "frame_%08d.png", frameIndex / blurFrameCount);
    sprintf(filenameBuffer2, "%s%s", outputPath.c_str(), filenameBuffer);
	return getAbsolutePathForFilename(filenameBuffer2);
}

double AnimationProcessor::getT() const
{
    if (blurBetweenRows)
        return (frameIndex / blurFrameCount) + (frameIndex % blurFrameCount) * 0.5 / blurFrameCount;
    else
        return frameIndex;
}

bool AnimationProcessor::isSwitchingMotionBlurGroup() const
{
    return blurFrameCount > 1 && (frameIndex % blurFrameCount == blurFrameCount - 1);
}

void AnimationProcessor::processNextFrame()
{
	animation->getState(getT(), animationState);
	frameIndex++;
}

unsigned int AnimationProcessor::getFrameIndex() const
{
    return frameIndex;
}

bool AnimationProcessor::isWithinAnimation() const
{
    return getT() < animation->getMaxT();
}
