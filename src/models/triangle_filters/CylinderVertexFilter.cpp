#include "CylinderVertexFilter.hpp"

CylinderVertexFilter::CylinderVertexFilter(
	double radius, double px, double py, double pz, double dx, double dy, double dz):
	position(px, py, pz), radius(radius), dx(dx), dy(dy), dz(dz)
{

}

bool CylinderVertexFilter::isIncluded(const Vertex&v) const
{
	return true;
}
