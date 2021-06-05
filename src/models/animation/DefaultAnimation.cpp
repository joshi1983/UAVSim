#include "DefaultAnimation.hpp"
#include <cmath>
#include <limits>

void DefaultAnimation::getState(double t, AnimationState &state) const
{
    AnimationState newState;
    newState.bladeAngle = t * 20.0;
    newState.yaw = 40;
    newState.x = 0;
    newState.y = 5 + 5 * sin(t * 0.1);
    newState.z = 0;
    newState.steerAngle1 = 15 * sin(t);
    newState.steerAngle2 = 15 * sin(t * 0.5);
    newState.cameraZ = -3;

    state = newState;
}

unsigned int DefaultAnimation::getMaxT() const
{
    return std::numeric_limits<unsigned int>::max();
}
