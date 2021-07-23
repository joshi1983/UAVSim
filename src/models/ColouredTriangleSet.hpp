#ifndef COLOURED_TRIANGLE_SET_HEADER
#define COLOURED_TRIANGLE_SET_HEADER
#include "Triangle.hpp"
#include <vector>
#include "Colour.hpp"

class ColouredTriangleSet
{
	public:
		ColouredTriangleSet(double r, double g, double b);
		Colour c;
		std::vector<Triangle> triangles;
		void draw() const;
};

#endif