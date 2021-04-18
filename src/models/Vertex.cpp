#include "Vertex.hpp"
#include <cmath>

Vertex::Vertex(): x(0), y(0), z(0)
{
}

Vertex::Vertex(double x, double y, double z): x(x), y(y), z(z)
{
}

Vertex::Vertex(const Vertex & other): x(other.x), y(other.y), z(other.z)
{
}

Vertex Vertex::operator-(const Vertex& other) const
{
	return Vertex(x - other.x, y - other.y, z - other.z);
}

Vertex Vertex::operator*(double scale) const
{
	return Vertex(scale * x, scale * y, scale * z);
}

double Vertex::dot(const Vertex& other) const
{
	return x * other.x +
		y * other.y + 
		z * other.z;
}

double Vertex::magnitude() const
{
	return sqrt(x * x + y * y + z * z);
}

Vertex Vertex::cross(const Vertex & other) const
{
	return Vertex(y * other.z - z * other.y,
		-(x * other.z - z * other.x),
		x * other.y - y * other.x);
}