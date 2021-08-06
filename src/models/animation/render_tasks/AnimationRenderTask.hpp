#ifndef ANIMATION_RENDER_TASK_HEADER_INCLUDED
#define ANIMATION_RENDER_TASK_HEADER_INCLUDED
#include "RenderTask.hpp"
#include "../StateSequenceAnimation.hpp"
#include "BitmapGenerationListener.hpp"

class AnimationRenderTask: public RenderTask, public BitmapGenerationListener
{
	private:
		int frameIndex;
	public:
		AnimationRenderTask(RenderTask * parent,
			const StateSequenceAnimation & stateSequenceAnimation);
		virtual void handle(Gdiplus::Bitmap * bitmap);
		virtual std::string getTypeName() const;
};

#endif
