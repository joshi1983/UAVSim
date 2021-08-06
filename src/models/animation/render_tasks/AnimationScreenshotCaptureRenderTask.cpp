#include "AnimationScreenshotCaptureRenderTask.hpp"
#include "../../../io/screenshots/screenshots.hpp"
using namespace std;

AnimationScreenshotCaptureRenderTask::AnimationScreenshotCaptureRenderTask(
	RenderTask * parent, const AnimationStateUpdater* animationStateUpdater, BitmapGenerationListener * listener, double widthRatio, double heightRatio, double leftRatio, double topRatio):
	RenderTask(parent), animationStateUpdater(animationStateUpdater), listener(listener), widthRatio(widthRatio), heightRatio(heightRatio), leftRatio(leftRatio), topRatio(topRatio)
{
}

void AnimationScreenshotCaptureRenderTask::processScreenshot()
{
	Gdiplus::Bitmap * bitmap = getScreenshotBitmap();
	listener->handle(bitmap);
}

string AnimationScreenshotCaptureRenderTask::getTypeName() const
{
	return "Animation Screenshot Capture Render Task";
}

void AnimationScreenshotCaptureRenderTask::getViewport(RenderViewport & result) const
{
	result.leftRatio = leftRatio;
	result.topRatio = topRatio;
	result.widthRatio = widthRatio;
	result.heightRatio = heightRatio;
}

void AnimationScreenshotCaptureRenderTask::updateAnimationStateForCurrentTask(AnimationState & state) const
{
	animationStateUpdater->updateAnimationStateForCurrentTask(state);
}