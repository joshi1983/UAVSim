#ifndef FULL_RESOLUTION_SAMPLE_RENDER_TASK_HEADER_INCLUDED
#define FULL_RESOLUTION_SAMPLE_RENDER_TASK_HEADER_INCLUDED
#include "RenderTask.hpp"
#include "BitmapGenerationListener.hpp"
#include "../StateSequenceAnimation.hpp"
#include "../AnimationState.hpp"

class FullResolutionSampleRenderTask: public RenderTask, public BitmapGenerationListener
{
	private:
		const AnimationStateUpdater * animationStateUpdater;
		BitmapGenerationListener* listener;
		AnimationState animationState;
	public:
		FullResolutionSampleRenderTask(RenderTask* parent,
			const AnimationStateUpdater * animationStateUpdater,
			BitmapGenerationListener* listener, double time,
			const StateSequenceAnimation & animation);
		virtual void handle(Gdiplus::Bitmap * bitmap) override;
		virtual void updateAnimationStateForCurrentTask(AnimationState & state) const override;
		virtual std::string getTypeName() const;
};

#endif
