#include "DefaultAnimation.hpp"
#include "../../physics/UAVPhysicalState.hpp"
#include <cmath>
#include <limits>
#include <iostream>
using namespace std;

DefaultAnimation* DefaultAnimation::singleton = nullptr;

DefaultAnimation::DefaultAnimation()
{

}

DefaultAnimation* DefaultAnimation::getInstance()
{
    if (DefaultAnimation::singleton == nullptr)
        DefaultAnimation::singleton = new DefaultAnimation();
    return singleton;
}

void DefaultAnimation::setAnimationState(const AnimationState & newState)
{
    remoteState = newState;
}

void DefaultAnimation::getState(double t, AnimationState &state) const
{
    state = remoteState;
    UAVPhysicalState* physicsState = UAVPhysicalState::getInstance();
    physicsState->copyInto(state);
}

unsigned int DefaultAnimation::getMaxT() const
{
    return std::numeric_limits<unsigned int>::max();
}
