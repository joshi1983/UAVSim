#ifndef ANIMATION_FRAME_RENDER_TASK_HEADER_INCLUDED
#define ANIMATION_FRAME_RENDER_TASK_HEADER_INCLUDED
#include "RenderTask.hpp"
#include "../StateSequenceAnimation.hpp"
#include "BitmapGenerationListener.hpp"

class AnimationFrameRenderTask: public RenderTask, public BitmapGenerationListener
{
	private:
		BitmapGenerationListener * listener;
		std::vector<Gdiplus::Bitmap*> bitmaps;
		unsigned int numBitmapsRequired;
	public:
		AnimationFrameRenderTask(RenderTask * parent,
			double startTime, double endTime,
			const StateSequenceAnimation & animation,
			BitmapGenerationListener * listener);
		virtual void handle(Gdiplus::Bitmap * bitmap);
		virtual std::string getTypeName() const;
};

#endif
