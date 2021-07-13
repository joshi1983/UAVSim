#include "Vector3D.hpp"
#include <cmath>
#include <sstream>
using namespace std;

Vector3D::Vector3D(): x(0), y(0), z(0)
{
}

Vector3D::Vector3D(double x, double y, double z): x(x), y(y), z(z)
{
}

Vector3D::Vector3D(const Vector3D & other): x(other.x), y(other.y), z(other.z)
{
}

Vector3D Vector3D::operator-(const Vector3D& other) const
{
	return Vector3D(x - other.x, y - other.y, z - other.z);
}

Vector3D& Vector3D::operator=(const Vector3D& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

Vector3D Vector3D::operator*(double scale) const
{
	return Vector3D(scale * x, scale * y, scale * z);
}

Vector3D operator*(double scale, const Vector3D & v)
{
    return Vector3D(v) * scale;
}

double Vector3D::dot(const Vector3D& other) const
{
	return x * other.x +
		y * other.y +
		z * other.z;
}

string Vector3D::str() const
{
    stringstream s;
    s << "{\"x\": " << x << ", \"y\": " << y << ", \"z\": " << z << "}";
    return s.str();
}

double Vector3D::magnitude() const
{
	return sqrt(x * x + y * y + z * z);
}

void Vector3D::normalize()
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

Vector3D Vector3D::cross(const Vector3D & other) const
{
	return Vector3D(y * other.z - z * other.y,
		-(x * other.z - z * other.x),
		x * other.y - y * other.x);
}

Vector3D Vector3D::operator+(const Vector3D& other) const
{
    return Vector3D(x + other.x, y + other.y, z + other.z);
}

Vector3D Vector3D::operator/(double scale) const
{
    scale = 1.0 / scale; // since multiplication is faster than division.
    return Vector3D(x * scale, y * scale, z * scale);
}

Vector3D& Vector3D::operator+=(const Vector3D& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}
