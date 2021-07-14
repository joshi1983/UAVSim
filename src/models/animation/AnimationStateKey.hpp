#ifndef ANIMATION_STATE_KEY_HEADER_INCLUDED
#define ANIMATION_STATE_KEY_HEADER_INCLUDED
#include <string>

class AnimateStateKey
{
    public:
        AnimateStateKey(const std::string&, double, double);
        std::string name;
        double rangeMin;
        double rangeMax;
};

#endif