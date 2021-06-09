#ifndef TRIANGLE_HEADER
#define TRIANGLE_HEADER

#include "Vertex.hpp"
#include <string>

class Triangle
{
	public:
		Vertex vertices[3];
		Vector3D cachedNormal;
		void updateNormal();
		std::string str() const;
};

#endif
