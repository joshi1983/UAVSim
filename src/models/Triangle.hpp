#ifndef TRIANGLE_HEADER
#define TRIANGLE_HEADER

#include "Vertex.hpp"

class Triangle
{
	public:
		Vertex vertices[3];
		Vertex cachedNormal;
		void updateNormal();
};

#endif
