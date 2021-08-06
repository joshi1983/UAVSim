#include "AnimationScreenshotCaptureRenderTask.hpp"
using namespace std;

AnimationScreenshotCaptureRenderTask::AnimationScreenshotCaptureRenderTask(RenderTask * parent):
	RenderTask(parent)
{
}

string AnimationScreenshotCaptureRenderTask::getTypeName() const
{
	return "Animation Screenshot Capture Render Task";
}
