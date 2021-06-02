#ifndef VERTEX_FILTER_HEADER_INCLUDED
#define VERTEX_FILTER_HEADER_INCLUDED
#include "../Vertex.hpp"

class VertexFilter
{
	public:
		virtual bool isIncluded(const Vertex&v) const = 0;
};

#endif