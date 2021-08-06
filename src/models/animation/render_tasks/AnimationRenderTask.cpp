#include "AnimationRenderTask.hpp"
#include "../ffmpeg.hpp"
#include "AnimationFrameRenderTask.hpp"
using namespace std;

AnimationRenderTask::AnimationRenderTask(RenderTask * parent, const StateSequenceAnimation & animation): RenderTask(parent)
{
    // create a MotionBlurRenderTask for each and every frame needed for animation.
    int fps = getFPS();
    int numFrames = animation.getMaxT() * fps;
    for (int i = 0; i <= numFrames; i++)
    {
        double t = i / (double)fps;
        double tEnd = t + 0.5 / fps;
        children.push_back(new AnimationFrameRenderTask(this, t, tEnd, animation));
    }
}

string AnimationRenderTask::getTypeName() const
{
	return "Animation Render Task";
}
