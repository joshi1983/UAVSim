#include "Triangle.hpp"
#include <sstream>
using namespace std;

void Triangle::updateNormal()
{
	// perform cross product.
	Vertex a = vertices[1] - vertices[0];
	Vertex b = vertices[2] - vertices[0];
	Vertex result = a.cross(b);
	cachedNormal = result * (1 / result.magnitude());
}

string Triangle::str() const
{
    stringstream s;
    s << "Triangle [";
    for (unsigned int i = 0; i < 3; i++)
    {
        if (i != 0)
            s << ", ";
        s << vertices[i].str();
    }
    return s.str() + "]";
}
