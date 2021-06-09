#include "CubeVertexFilter.hpp"
#include <iostream>
#include <sstream>
using namespace std;

CubeVertexFilter::CubeVertexFilter(
	double minX, double minY, double minZ, double maxX, double maxY, double maxZ):
	minX(minX), minY(minY), minZ(minZ), maxX(maxX), maxY(maxY), maxZ(maxZ)
{
}

bool CubeVertexFilter::isIncluded(const Vertex&v) const
{
	return (v.p.x >= minX) && (v.p.x <= maxX) &&
		(v.p.y >= minY) && (v.p.y <= maxY) &&
		(v.p.z >= minZ) && (v.p.z <= maxZ);
}

string CubeVertexFilter::str() const
{
    stringstream s;
    s << "{\"type\": \"cube\", \"minX\": " << minX
        << ", \"minY\": " << minY << ", \"minZ\": "
        << minZ << ", \"maxX\": " << maxX << ", \"maxY\": " <<
        maxY << ", \"maxZ\": " << maxZ << "}";
    return s.str();
}
