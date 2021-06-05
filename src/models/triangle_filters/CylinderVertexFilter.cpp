#include "CylinderVertexFilter.hpp"
#include <sstream>
#include <iostream>
using namespace std;

CylinderVertexFilter::CylinderVertexFilter(
	double radius, double px, double py, double pz, double dx, double dy, double dz):
	position(px, py, pz), radius(radius), direction(dx, dy, dz)
{
    direction.normalize();
}

bool CylinderVertexFilter::isIncluded(const Vertex&v) const
{
    /*
    This is based on math explained at:
    https://www.geometrictools.com/Documentation/DistancePointLine.pdf
    */
    Vertex displacement = (v - position);
    double t = displacement.dot(direction);
	double distanceFromLine = (t * direction - displacement).magnitude();
	return distanceFromLine <= radius;
}

string CylinderVertexFilter::str() const
{
    stringstream s;
    s << "{\"type\": \"cylinder\","
        << "\"radius\": " << radius << ", \"from\": "
        << position.str() << ", \"direction\": " << direction.str()
        << "}";
    return s.str();
}
