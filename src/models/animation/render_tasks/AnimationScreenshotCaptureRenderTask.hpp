#ifndef ANIMATION_SCREENSHOT_CAPTURE_RENDER_TASK_HEADER_INCLUDED
#define ANIMATION_SCREENSHOT_CAPTURE_RENDER_TASK_HEADER_INCLUDED
#include "RenderTask.hpp"

class AnimationScreenshotCaptureRenderTask: public RenderTask
{
	public:
		AnimationScreenshotCaptureRenderTask(RenderTask * parent);
		virtual std::string getTypeName() const;
};

#endif