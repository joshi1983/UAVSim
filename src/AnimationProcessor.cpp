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

AnimationProcessor::AnimationProcessor(Animation* animation,
	AnimationState & animationState):
	animation(animation), animationState(animationState), frameIndex(0)
{
    UAVSimConfig& c = UAVSimConfig::config;
    string path("/blurFrameCount");
    Value* a =  Pointer(path.c_str()).Get(c.doc);
    if (a != nullptr)
    {
        blurFrameCount = a->GetUint();
        cerr << "Loaded blurFrameCount of " << blurFrameCount << endl;
    }
    else
        blurFrameCount = 1;
}

string AnimationProcessor::getFileName() const
{
	char filenameBuffer[256];
	char filenameBuffer2[256];
	if (blurFrameCount == 1)
        sprintf(filenameBuffer, "frame_%08d.png", frameIndex);
    else
        sprintf(filenameBuffer, "frame_%08d_%08d.png", frameIndex / blurFrameCount, frameIndex % blurFrameCount);

    sprintf(filenameBuffer2, "outputs/frames/%s", filenameBuffer);
	return getAbsolutePathForFilename(filenameBuffer2);
}

void AnimationProcessor::processNextFrame()
{
	animation->getState(frameIndex, animationState);
	frameIndex++;
}

unsigned int AnimationProcessor::getFrameIndex() const
{
    return frameIndex;
}

bool AnimationProcessor::isWithinAnimation() const
{
    return frameIndex < animation->getMaxT();
}
