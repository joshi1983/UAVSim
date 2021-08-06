#ifndef MOTION_BLUR_RENDER_TASK_HEADER_INCLUDED
#define MOTION_BLUR_RENDER_TASK_HEADER_INCLUDED
#include "RenderTask.hpp"
#include "../StateSequenceAnimation.hpp"

class MotionBlurRenderTask: public RenderTask
{
	public:
		MotionBlurRenderTask(RenderTask * parent,
		    double startTime, double endTime, const StateSequenceAnimation & animation);
		// children are AnimationScreenshotCaptureRenderTask
		virtual std::string getTypeName() const;
};

#endif
