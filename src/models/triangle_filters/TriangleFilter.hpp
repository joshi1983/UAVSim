#ifndef TRIANGLE_FILTER_HEADER_INCLUDED
#define TRIANGLE_FILTER_HEADER_INCLUDED
#include "../Triangle.hpp"
#include "VertexFilter.hpp"
#include <vector>

class TriangleFilter {
	private:
		unsigned int minimumRequired;
		const VertexFilter * vf;
	public:
		TriangleFilter(unsigned int minimumRequired, VertexFilter * vf);
		void removeFrom(std::vector<Triangle>& triangles) const;
		virtual bool isIncluded(const Triangle & t) const;
		virtual ~TriangleFilter();
		friend std::ostream& operator<<(std::ostream &strm, const TriangleFilter &tf);
};

std::ostream& operator<<(std::ostream &strm, const TriangleFilter &tf);

#endif
