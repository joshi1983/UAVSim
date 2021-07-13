#include "DefaultAnimation.hpp"
#include <cmath>
#include <limits>

DefaultAnimation* DefaultAnimation::main = nullptr;

DefaultAnimation::DefaultAnimation()
{
    if (DefaultAnimation::main == nullptr)
        DefaultAnimation::main = this;
}

void DefaultAnimation::setAnimationState(const AnimationState & newState)
{
    remoteState = newState;
    isControlledRemotely = true;
}

void DefaultAnimation::getState(double t, AnimationState &state) const
{
    if (isControlledRemotely)
        state = remoteState;
    else
    {
        AnimationState newState;
        newState.blade1Angle = t * 20.0;
        newState.blade2Angle = -t * 20.0;
        newState.yaw = 50;
        newState.x = 0;
        newState.y = 0.01 + 0.01 * sin(t * 0.1);
        newState.z = 0;
        newState.steerAngle1 = 15 * sin(t);
        newState.steerAngle2 = 15 * sin(t * 0.5);
        newState.cameraZ = -0.3;
        newState.waterAnimationT = t;

        state = newState;
    }
}

unsigned int DefaultAnimation::getMaxT() const
{
    return std::numeric_limits<unsigned int>::max();
}
