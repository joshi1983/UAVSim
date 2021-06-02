#ifndef TRIANGLE_FILTER_HEADER_INCLUDED
#define TRIANGLE_FILTER_HEADER_INCLUDED
#include "../Triangle.hpp"
#include "VertexFilter.hpp"

class TriangleFilter {
	private:
		unsigned int minimumRequired;
		const VertexFilter * vf;
	public:
		TriangleFilter(unsigned int minimumRequired, VertexFilter * vf);
		virtual bool isIncluded(const Triangle & t) const;
		virtual ~TriangleFilter();
};

#endif
