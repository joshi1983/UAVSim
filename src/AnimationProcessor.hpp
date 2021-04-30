#ifndef ANIMATION_PROCESSOR_HEADER_INCLUDED
#define ANIMATION_PROCESSOR_HEADER_INCLUDED
#include "models/animation/Animation.hpp"

class AnimationProcessor
{
	private:
		Animation* animation;
		AnimationState& animationState;
		unsigned int frameIndex;
	public:
		AnimationProcessor(Animation* animation, AnimationState & animationState);
		void processNextFrame();
};

#endif
