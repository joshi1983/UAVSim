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
	public:
		AnimationProcessor(Animation* animation, AnimationState & animationState);
		void processNextFrame();
		std::string getFileName() const;
		unsigned int getFrameIndex() const;
		bool isWithinAnimation() const;
};

#endif
