#ifndef ANIMATION_STATE_KEY_HEADER_INCLUDED
#define ANIMATION_STATE_KEY_HEADER_INCLUDED
#include <string>

enum AnimationStateKeyType
{
	tDouble = 0,
	tColour = 1
};

class AnimateStateKey
{
    public:
        AnimateStateKey(const std::string&, const AnimationStateKeyType &, double, double);
		AnimationStateKeyType dataType;
        std::string name;
        double rangeMin;
        double rangeMax;
};

#endif
