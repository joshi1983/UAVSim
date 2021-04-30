#ifndef DEFAULT_ANIMATION_HEADER_INCLUDED
#define DEFAULT_ANIMATION_HEADER_INCLUDED
#include "Animation.hpp"

class DefaultAnimation: public Animation
{
	public:
		virtual void getState(double t, AnimationState &state) const override;
};

#endif
