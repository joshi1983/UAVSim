#include "MotionBlurRenderTask.hpp"
using namespace std;

MotionBlurRenderTask::MotionBlurRenderTask(RenderTask * parent,
    double startTime, double endTime, const StateSequenceAnimation & animation):
    RenderTask(parent)
{
}

string MotionBlurRenderTask::getTypeName() const
{
	return "Motion Blur Render Task";
}
