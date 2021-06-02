#include "UnionVertexFilter.hpp"
using namespace std;

UnionVertexFilter::UnionVertexFilter(const std::vector<VertexFilter*>& filters):
	filters(filters)
{
}

bool UnionVertexFilter::isIncluded(const Vertex&v) const
{
	for (auto it = filters.begin(); it != filters.end(); it++)
	{
		if ((*it)->isIncluded(v))
			return true;
	}
	return false;
}

UnionVertexFilter::~UnionVertexFilter()
{
    // FIXME: make sure all filters are deleted.
}
