#include "Vertex.hpp"
using namespace std;

Vertex::Vertex(): p(0, 0, 0)
{
}

Vertex::Vertex(double x, double y, double z): p(x, y, z)
{
}

Vertex::Vertex(const Vertex & other): p(other.p)
{
}

Vertex& Vertex::operator=(const Vertex& other)
{
	p = other.p;
	return *this;
}

string Vertex::str() const
{
    return p.str();
}
