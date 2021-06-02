#include "CubeVertexFilter.hpp"

CubeVertexFilter::CubeVertexFilter(
	double minX, double minY, double minZ, double maxX, double maxY, double maxZ):
	minX(minX), minY(minY), minZ(minZ), maxX(maxX), maxY(maxY), maxZ(maxZ)
{

}

bool CubeVertexFilter::isIncluded(const Vertex&v) const
{
	return v.x >= minX && v.x <= maxX &&
		v.y >= minY && v.y <= maxY &&
		v.z >= minZ && v.z <= maxZ;
}
