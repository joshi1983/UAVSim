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
	return (v.x >= minX) && (v.x <= maxX) &&
		(v.y >= minY) && (v.y <= maxY) &&
		(v.z >= minZ) && (v.z <= maxZ);
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
