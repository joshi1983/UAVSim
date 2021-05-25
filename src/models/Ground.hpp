#ifndef GROUND_HEADER_INCLUDED
#define GROUND_HEADER_INCLUDED
#include "animation/AnimationState.hpp"

class Ground
{
	public:
		void draw(int windowid, const AnimationState & animationState, double yOffset) const;
		static void init(int windowid);
};

#endif
