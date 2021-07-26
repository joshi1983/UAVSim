#ifndef COLOURED_TRIANGLE_SET_HEADER
#define COLOURED_TRIANGLE_SET_HEADER
#include "Triangle.hpp"
#include <vector>
#include "animation/TriangleSetAnimationProperties.hpp"

class ColouredTriangleSet
{
	public:
		ColouredTriangleSet(double r, double g, double b);
		TriangleSetAnimationProperties animationProperties;
		std::vector<Triangle> triangles;
		void draw() const;
};

#endif