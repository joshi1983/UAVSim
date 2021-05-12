#include "AnimationProcessor.hpp"
#include "io/screenshots/screenshots.hpp"
#include <cstdio>
using namespace std;

AnimationProcessor::AnimationProcessor(Animation* animation,
	AnimationState & animationState):
	animation(animation), animationState(animationState), frameIndex(0)
{
}

void AnimationProcessor::processNextFrame()
{
	animation->getState(frameIndex, animationState);
	char filename[256];
	sprintf(filename, "frame_%08d.png", frameIndex);
	saveScreenshot(filename);
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
