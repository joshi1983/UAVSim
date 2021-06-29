#ifndef STATE_SEQUENCE_ANIMATION_HEADER_INCLUDED
#define STATE_SEQUENCE_ANIMATION_HEADER_INCLUDED
#include "Animation.hpp"
#include <vector>

class StateSequenceAnimation: public Animation
{
	private:
		std::vector<AnimationState> states;
	public:
		StateSequenceAnimation(std::vector<AnimationState> states);
        virtual void getState(double t, AnimationState &state) const override;
		virtual unsigned int getMaxT() const override;
};

#endif
