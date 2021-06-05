#ifndef INTERSECTION_VERTEX_FILTER_HEADER_INCLUDED
#define INTERSECTION_VERTEX_FILTER_HEADER_INCLUDED
#include "VertexFilter.hpp"
#include <vector>

class IntersectionVertexFilter: public VertexFilter
{
	private:
		std::vector<VertexFilter *> filters;
	public:
		IntersectionVertexFilter(const std::vector<VertexFilter *>& filters);
		virtual bool isIncluded(const Vertex& v) const override;
		virtual ~IntersectionVertexFilter();
		virtual std::string str() const;
};

#endif
