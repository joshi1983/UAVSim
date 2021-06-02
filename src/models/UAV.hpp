#ifndef UAV_HEADER_INCLUDED
#define UAV_HEADER_INCLUDED
#include "animation/AnimationState.hpp"

class UAV
{
	public:
		UAV();
		void draw(const AnimationState & state, double yOffset) const;
};

#endif