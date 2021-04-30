#include "StateSequenceAnimation.hpp"
using namespace std;

StateSequenceAnimation::StateSequenceAnimation(vector<AnimationState> states): states(states)
{
}

void StateSequenceAnimation::getState(double t, AnimationState &state) const
{
	int tI = (int)t;
	if (tI < 0)
		tI = 0;
	if ((unsigned int)tI >= states.size())
		tI = states.size() - 1;
	state = states[tI];
}
