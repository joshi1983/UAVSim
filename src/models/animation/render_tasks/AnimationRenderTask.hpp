#ifndef ANIMATION_RENDER_TASK_HEADER_INCLUDED
#define ANIMATION_RENDER_TASK_HEADER_INCLUDED
#include "RenderTask.hpp"
#include "../StateSequenceAnimation.hpp"

class AnimationRenderTask: public RenderTask
{
	public:
		AnimationRenderTask(RenderTask * parent, const StateSequenceAnimation & stateSequenceAnimation);
		virtual std::string getTypeName() const;
};

#endif