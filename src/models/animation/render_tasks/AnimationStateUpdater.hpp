#ifndef ANIMATION_STATE_UPDATER_HEADER_INCLUDED
#define ANIMATION_STATE_UPDATER_HEADER_INCLUDED

class AnimationStateUpdater
{
	public:
		virtual void updateAnimationStateForCurrentTask(AnimationState & state) const = 0;
};

#endif