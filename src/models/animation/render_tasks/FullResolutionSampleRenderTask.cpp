#include "FullResolutionSampleRenderTask.hpp"
#include "AnimationScreenshotCaptureRenderTask.hpp"
#include "../Resolution.hpp"
using namespace std;

FullResolutionSampleRenderTask::FullResolutionSampleRenderTask(
	RenderTask* parent, const AnimationStateUpdater * animationStateUpdater,
	BitmapGenerationListener* listener, double time,
	const StateSequenceAnimation & animation):
	RenderTask(parent), listener(listener)
{
	animation.getState(time, animationState);
	int numColumns, numRows;
	getSuggestedWindowGrid(numColumns, numRows);

	// FIXME: adjust if multiple parts need to be stitched together.
	// Create all the necessary parts.
	children.push_back(new AnimationScreenshotCaptureRenderTask(this, this, this, 1, 1, 0, 0));
}

string FullResolutionSampleRenderTask::getTypeName() const
{
	return "Full Resolution Sample Render Task";
}

void FullResolutionSampleRenderTask::updateAnimationStateForCurrentTask(AnimationState & state) const
{
	state = animationState;
}

void FullResolutionSampleRenderTask::handle(Gdiplus::Bitmap * bitmap)
{
	// FIXME: adjust if multiple bitmaps need to be stitched together.
	listener->handle(bitmap);
}
