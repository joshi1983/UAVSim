#ifndef DEFAULT_ANIMATION_HEADER_INCLUDED
#define DEFAULT_ANIMATION_HEADER_INCLUDED
#include "Animation.hpp"

class DefaultAnimation: public Animation
{
    private:
        AnimationState remoteState;
	    DefaultAnimation();
		static DefaultAnimation* singleton;
	public:
	    void setAnimationState(const AnimationState & newState);
        virtual void getState(double t, AnimationState &state) const override;
		virtual unsigned int getMaxT() const override;
		static DefaultAnimation* getInstance();
};

#endif
