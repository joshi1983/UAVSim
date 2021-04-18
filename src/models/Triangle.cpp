#include "Triangle.hpp"

void Triangle::updateNormal()
{
	// perform cross product.
	Vertex a = vertices[1] - vertices[0];
	Vertex b = vertices[2] - vertices[0];
	Vertex result = a.cross(b);
	cachedNormal = result * (1 / result.magnitude());
}
