#ifndef TRIANGLE_SET_ANIMATION_PROPERTIES_HEADER_INCLUDED
#define TRIANGLE_SET_ANIMATION_PROPERTIES_HEADER_INCLUDED
#include "../Colour.hpp"

class TriangleSetAnimationProperties
{
	public:
		TriangleSetAnimationProperties();
		TriangleSetAnimationProperties(bool isVisible, const Colour& colour);
		TriangleSetAnimationProperties(const TriangleSetAnimationProperties& other);
		TriangleSetAnimationProperties& operator=(const TriangleSetAnimationProperties& other);
		static TriangleSetAnimationProperties blend(const TriangleSetAnimationProperties& p1, const TriangleSetAnimationProperties & p2, double ratio);
		bool isVisible;
		Colour colour;
};

#endif
