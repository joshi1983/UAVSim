#ifndef UNION_VERTEX_FILTER_HEADER_INCLUDED
#define UNION_VERTEX_FILTER_HEADER_INCLUDED
#include "VertexFilter.hpp"
#include <vector>

class UnionVertexFilter: public VertexFilter
{
	private:
		std::vector<VertexFilter*> filters;
	public:
		UnionVertexFilter(const std::vector<VertexFilter*>& filters);
		virtual bool isIncluded(const Vertex& v) const override;
		virtual ~UnionVertexFilter();
		virtual std::string str() const override;
};

#endif
