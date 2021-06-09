#ifndef VERTEX_HEADER
#define VERTEX_HEADER
#include <string>
#include "Vector3D.hpp"

class Vertex
{
	public:
		Vector3D p;
		Vertex();
		Vertex(double x, double y, double z);
		Vertex(const Vertex & other);
		Vertex& operator=(const Vertex& other);
		std::string str() const;
};

#endif
