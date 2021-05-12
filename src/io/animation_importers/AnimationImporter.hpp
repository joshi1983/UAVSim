#ifndef ANIMATION_HEADER_INCLUDED
#define ANIMATION_HEADER_INCLUDED
#include <string>
#include "../../models/animation/StateSequenceAnimation.hpp"

class AnimationImporter
{
	public:
		virtual StateSequenceAnimation* loadFrom(const std::string & filename) const = 0;
};

#endif
