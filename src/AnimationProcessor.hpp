#ifndef ANIMATION_PROCESSOR_HEADER_INCLUDED
#define ANIMATION_PROCESSOR_HEADER_INCLUDED
#include "models/animation/Animation.hpp"

class AnimationProcessor
{
	private:
		Animation* animation;
		AnimationState& animationState;
		unsigned int frameIndex;
		unsigned int blurFrameCount;
		double getT() const;
	public:
		AnimationProcessor(Animation* animation, AnimationState & animationState);
		void processNextFrame();
		bool isSwitchingMotionBlurGroup() const;
		std::string getBlurGroupFileName() const;
		std::string getFileName() const;
		unsigned int getFrameIndex() const;
		bool isWithinAnimation() const;
};

#endif
