#include "AnimationFrameRenderTask.hpp"
using namespace std;

AnimationFrameRenderTask::AnimationFrameRenderTask(RenderTask * parent,
    double startTime, double endTime, const StateSequenceAnimation & animation): RenderTask(parent)
{
    // FIXME: decide if MotionBlurRenderTasks are needed.
}

string AnimationFrameRenderTask::getTypeName() const
{
	return "Frame Render Task";
}
