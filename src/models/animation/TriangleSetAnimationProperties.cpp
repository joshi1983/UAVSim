#include "TriangleSetAnimationProperties.hpp"
#include <iostream>
using namespace std;

TriangleSetAnimationProperties::TriangleSetAnimationProperties(): isVisible(true), colour(1, 1, 1)
{

}

TriangleSetAnimationProperties::TriangleSetAnimationProperties(bool isVisible, const Colour& colour):
	isVisible(isVisible), colour(colour)
{

}

TriangleSetAnimationProperties::TriangleSetAnimationProperties(const TriangleSetAnimationProperties& other):
	isVisible(other.isVisible), colour(other.colour)
{

}

TriangleSetAnimationProperties& TriangleSetAnimationProperties::operator=(const TriangleSetAnimationProperties& other)
{
	colour = other.colour;
	isVisible = other.isVisible;
	return *this;
}

TriangleSetAnimationProperties TriangleSetAnimationProperties::blend(const TriangleSetAnimationProperties& p1, const TriangleSetAnimationProperties & p2, double ratio)
{
	bool isVisible;// bool isn't continuous but we can treat 0.5 as a threshold.
	if (ratio < 0.5)
		isVisible = p1.isVisible;
	else
		isVisible = p2.isVisible;
	return TriangleSetAnimationProperties(isVisible,
		Colour::blend(p1.colour, p2.colour, ratio));
}
