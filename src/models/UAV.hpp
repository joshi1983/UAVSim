#ifndef UAV_HEADER_INCLUDED
#define UAV_HEADER_INCLUDED
#include "animation/AnimationState.hpp"
#include "UAVModel.hpp"

class UAV
{
    public:
		void draw(const AnimationState & state, double yOffset) const;
};

#endif
