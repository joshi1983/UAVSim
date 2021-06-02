#include "SphereVertexFilter.hpp"

SphereVertexFilter::SphereVertexFilter(double cx, double cy, double cz, double radius):
	cx(cx), cy(cy), cz(cz), radius(radius)
{
}

bool SphereVertexFilter::isIncluded(const Vertex& v) const
{
	return (v - Vertex(cx, cy, cz)).magnitude() <= radius;
}
