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

string outputPath = "outputs/frames/";
bool blurBetweenRows = false;

AnimationProcessor::AnimationProcessor(Animation* animation,
	AnimationState & animationState):
	animation(animation), animationState(animationState), frameIndex(0)
{
    UAVSimConfig& c = UAVSimConfig::config;
    string path("/csv/blurFrameCount");
    Value* a =  Pointer(path.c_str()).Get(c.doc);
    if (a != nullptr)
    {
        blurFrameCount = a->GetUint();
        cerr << "Loaded blurFrameCount of " << blurFrameCount << endl;
    }
    else
        blurFrameCount = 1;
    path = "/frameOutputDirectory";
    a =  Pointer(path.c_str()).Get(c.doc);
    if (a != nullptr)
    {
        outputPath = a->GetString();
    }
    if (outputPath[outputPath.length() - 1] != '/')
        outputPath += '/';

    path = "/csv/blurBetweenRows";
    a =  Pointer(path.c_str()).Get(c.doc);
    if (a != nullptr)
    {
        blurBetweenRows = a->GetBool();
    }
}

string AnimationProcessor::getFileName() const
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

double AnimationProcessor::getT() const
{
    if (blurBetweenRows)
        return (frameIndex / blurFrameCount) + (frameIndex % blurFrameCount) * 0.5 / blurFrameCount;
    else
        return frameIndex;
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
