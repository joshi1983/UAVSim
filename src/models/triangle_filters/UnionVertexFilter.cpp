#include "UnionVertexFilter.hpp"
using namespace std;

UnionVertexFilter::UnionVertexFilter(const std::vector<VertexFilter*>& filters):
	filters(filters)
{
}

bool UnionVertexFilter::isIncluded(const Vertex&v) const
{
	for (auto& filter: filters)
	{
		if (filter->isIncluded(v))
			return true;
	}
	return false;
}

UnionVertexFilter::~UnionVertexFilter()
{
    // FIXME: make sure all filters are deleted.
}

string UnionVertexFilter::str() const
{
    string result = "\"union\": [";
    bool needsComma = false;
	for (auto& filter: filters)
	{
	    if (needsComma)
            result += ", ";
	    result += filter->str();
	    needsComma = true;
	}

    return result + "]";
}
