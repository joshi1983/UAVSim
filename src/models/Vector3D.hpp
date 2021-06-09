#ifndef VECTOR_3D_HEADER_INCLUDED
#define VECTOR_3D_HEADER_INCLUDED

#include <string>

class Vector3D
{
	public:
		double x, y, z;
		Vector3D();
		Vector3D(double x, double y, double z);
		Vector3D(const Vector3D & other);
		Vector3D operator-(const Vector3D& other) const;
		Vector3D operator*(double scale) const;
		Vector3D operator=(const Vector3D& other);
		double dot(const Vector3D& other) const;
		double magnitude() const;
		void normalize();
		Vector3D cross(const Vector3D & other) const;
		std::string str() const;
};

Vector3D operator*(double scale, const Vector3D & v);

#endif