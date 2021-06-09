#include "SphereVertexFilter.hpp"
using namespace std;

SphereVertexFilter::SphereVertexFilter(double cx, double cy, double cz, double radius):
	cx(cx), cy(cy), cz(cz), radius(radius)
{
}

bool SphereVertexFilter::isIncluded(const Vertex& v) const
{
	return (v.p - Vector3D(cx, cy, cz)).magnitude() <= radius;
}

string SphereVertexFilter::str() const
{
    string result = "{\"type\": \"sphere\"}";
    return result;
}
