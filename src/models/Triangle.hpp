#ifndef TRIANGLE_HEADER
#define TRIANGLE_HEADER

#include "Vertex.hpp"
#include <string>

class Triangle
{
	public:
	    Triangle();
	    Triangle(const Triangle& triangle);
		Vertex vertices[3];
		Vector3D cachedNormal;
		void updateNormal();
		std::string str() const;
};

#endif
