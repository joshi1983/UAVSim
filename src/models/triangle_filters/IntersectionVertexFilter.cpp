#include "IntersectionVertexFilter.hpp"
using namespace std;

IntersectionVertexFilter::IntersectionVertexFilter(const std::vector<VertexFilter*>& filters):
	filters(filters)
{
}

bool IntersectionVertexFilter::isIncluded(const Vertex&v) const
{
	for (auto it = filters.begin(); it != filters.end(); it++)
	{
		if (!(*it)->isIncluded(v))
			return false;
	}
	return true;
}

IntersectionVertexFilter::~IntersectionVertexFilter()
{
    // FIXME: make sure all filters are deleted.
}
