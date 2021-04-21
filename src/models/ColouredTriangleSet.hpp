#ifndef COLOURED_TRIANGLE_SET_HEADER
#define COLOURED_TRIANGLE_SET_HEADER
#include "Triangle.hpp"
#include <vector>

class ColouredTriangleSet
{
	public:
		ColouredTriangleSet(double r, double g, double b);
		double r, g, b;
		std::vector<Triangle> triangles;
		void draw() const;
};

#endif