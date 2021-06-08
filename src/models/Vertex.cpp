#include "Vertex.hpp"
#include <cmath>
#include <sstream>
using namespace std;

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

Vertex Vertex::operator=(const Vertex& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
}

Vertex Vertex::operator*(double scale) const
{
	return Vertex(scale * x, scale * y, scale * z);
}

Vertex operator*(double scale, const Vertex & v)
{
    return Vertex(v) * scale;
}

double Vertex::dot(const Vertex& other) const
{
	return x * other.x +
		y * other.y +
		z * other.z;
}

string Vertex::str() const
{
    stringstream s;
    s << "{\"x\": " << x << ", \"y\": " << y << ", \"z\": " << z << "}";
    return s.str();
}

double Vertex::magnitude() const
{
	return sqrt(x * x + y * y + z * z);
}

void Vertex::normalize()
{
    double m = magnitude();
    if (m < 0.000001) // avoid division by 0.
    {
        x = 1;
        y = z = 0;
    }
    else {
        m = 1/m; // get reciprocal because multiplying is likely faster than dividing.
        x *= m;
        y *= m;
        z *= m;
    }
}

Vertex Vertex::cross(const Vertex & other) const
{
	return Vertex(y * other.z - z * other.y,
		-(x * other.z - z * other.x),
		x * other.y - y * other.x);
}
