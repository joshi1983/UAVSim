#ifndef ANIMATION_SCREENSHOT_CAPTURE_RENDER_TASK_HEADER_INCLUDED
#define ANIMATION_SCREENSHOT_CAPTURE_RENDER_TASK_HEADER_INCLUDED
#include "RenderTask.hpp"
#include "BitmapGenerationListener.hpp"

class AnimationScreenshotCaptureRenderTask: public RenderTask
{
	private:
		const AnimationStateUpdater * animationStateUpdater;
		BitmapGenerationListener * listener;
		double widthRatio;
		double heightRatio;
		double leftRatio;
		double topRatio;
	public:
		AnimationScreenshotCaptureRenderTask(RenderTask * parent,
			const AnimationStateUpdater * updater, BitmapGenerationListener * listener,
			double, double, double leftRatio, double topRatio);
		virtual void updateAnimationStateForCurrentTask(AnimationState & state) const override;
		virtual void processScreenshot() override;
		virtual void getViewport(RenderViewport & result) const override;
		virtual std::string getTypeName() const;
};

#endif
