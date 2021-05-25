#include "StateSequenceAnimation.hpp"
using namespace std;

StateSequenceAnimation::StateSequenceAnimation(vector<AnimationState> states): states(states)
{
}

void StateSequenceAnimation::getState(double t, AnimationState &state) const
{
	int tI = (int)t;
	if (tI < 0 || (unsigned int)tI >= states.size() - 1)
    {
        if (tI < 0)
            tI = 0;
        else
            tI = states.size() - 1;
        state = states[tI];
    }
    else {
        state = AnimationState::blend(states[tI], states[tI + 1], t - tI);
    }
}

unsigned int StateSequenceAnimation::getMaxT() const
{
    return states.size();
}
