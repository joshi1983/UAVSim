#include "DefaultAnimation.hpp"
#include <cmath>
#include <limits>

void DefaultAnimation::getState(double t, AnimationState &state) const
{
    AnimationState newState;
    newState.bladeAngle = t * 50.0;
    newState.yaw = t * 10;

    state = newState;
}

unsigned int DefaultAnimation::getMaxT() const
{
    return std::numeric_limits<unsigned int>::max();
}
