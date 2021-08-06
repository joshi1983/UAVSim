#include "AnimationFrameRenderTask.hpp"
#include "FullResolutionSampleRenderTask.hpp"
#include "../AnimationSettings.hpp"
#include "../../../io/screenshots/bitmapBlender.hpp"
using namespace std;

AnimationFrameRenderTask::AnimationFrameRenderTask(RenderTask * parent,
    double startTime, double endTime, const StateSequenceAnimation & animation,
	BitmapGenerationListener * listener):
	RenderTask(parent), listener(listener)
{
	numBitmapsRequired = getBlurSamplesPerFrame();
    for (unsigned int i = 0; i < numBitmapsRequired; i++)
    {
		double t = startTime + (endTime - startTime) * i / numBitmapsRequired;
        children.push_back(new FullResolutionSampleRenderTask(this, this, this, t, animation));
    }
}

void AnimationFrameRenderTask::handle(Gdiplus::Bitmap * bitmap)
{
	// blend all the bitmaps.
	bitmaps.push_back(bitmap);
	if (bitmaps.size() == numBitmapsRequired)
	{
		// if this is the last bitmap, blend and dispatch the resulting bitmap to listener.
		Gdiplus::Bitmap* result = motionBlend(bitmaps);
		listener->handle(result);
	}
}

string AnimationFrameRenderTask::getTypeName() const
{
	return "Frame Render Task";
}
