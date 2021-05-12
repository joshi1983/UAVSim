#ifndef _ANIMATION_HEADER_INCLUDED
#define _ANIMATION_HEADER_INCLUDED
#include "AnimationState.hpp"

class Animation
{
	public:
		virtual void getState(double t, AnimationState &state) const = 0;
		virtual unsigned int getMaxT() const = 0;
};

#endif
