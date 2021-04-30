#include "DefaultAnimation.hpp"
#include <cmath>

void DefaultAnimation::getState(double t, AnimationState &state) const
{
    AnimationState newState;
    newState.y = -1 + 1 * sin(t);
    newState.bladeAngle = t * 500.0;
    newState.yaw = t * 10;
    state = newState;
}
