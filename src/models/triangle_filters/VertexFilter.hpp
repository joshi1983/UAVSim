#ifndef VERTEX_FILTER_HEADER_INCLUDED
#define VERTEX_FILTER_HEADER_INCLUDED
#include "../Vertex.hpp"
#include <string>

class VertexFilter
{
	public:
		virtual bool isIncluded(const Vertex&v) const = 0;
		virtual std::string str() const = 0;
		virtual ~VertexFilter();
};

#endif
