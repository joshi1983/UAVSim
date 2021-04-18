#ifndef VERTEX_HEADER
#define VERTEX_HEADER

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
		Vertex cross(const Vertex & other) const;
};

#endif
