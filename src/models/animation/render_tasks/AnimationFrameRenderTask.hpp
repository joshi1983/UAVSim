#ifndef ANIMATION_FRAME_RENDER_TASK_HEADER_INCLUDED
#define ANIMATION_FRAME_RENDER_TASK_HEADER_INCLUDED
#include "RenderTask.hpp"
#include "../StateSequenceAnimation.hpp"

class AnimationFrameRenderTask: public RenderTask
{
	public:
		AnimationFrameRenderTask(RenderTask * parent, double startTime, double endTime, const StateSequenceAnimation & animation);
		virtual std::string getTypeName() const;
};

#endif
