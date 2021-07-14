#ifndef ANIMATION_PROCESSOR_HEADER_INCLUDED
#define ANIMATION_PROCESSOR_HEADER_INCLUDED
#include "Animation.hpp"

class AnimationProcessor
{
	private:
		Animation* animation;
		AnimationState& animationState;
		unsigned int frameIndex;
		unsigned int blurFrameCount;
		double getT() const;
		static std::string getFileName(int frameIndex, int blurFrameCount);
	public:
		AnimationProcessor(Animation* animation, AnimationState & animationState);
		void processNextFrame();
		bool isSwitchingMotionBlurGroup() const;
		std::string getBlurGroupFileName() const;
		std::string getFileName() const;
		unsigned int getFrameIndex() const;
		bool isWithinAnimation() const;
		void deleteFrameAfterAnimation() const;
            // FIXME: delete next frame index if it exists so the mp4 doesn't show old frames
            // that existed before the new frames were generated\.

};

#endif
