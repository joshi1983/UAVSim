#ifndef VERTEX_HEADER
#define VERTEX_HEADER
#include <string>

class Vertex
{
	public:
		double x, y, z;
		Vertex();
		Vertex(double x, double y, double z);
		Vertex(const Vertex & other);
		Vertex operator-(const Vertex& other) const;
		Vertex operator*(double scale) const;
		double dot(const Vertex& other) const;
		double magnitude() const;
		void normalize();
		Vertex cross(const Vertex & other) const;
		std::string str() const;
};

Vertex operator*(double scale, const Vertex & v);

#endif
