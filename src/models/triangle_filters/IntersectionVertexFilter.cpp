#include "IntersectionVertexFilter.hpp"
#include <sstream>
using namespace std;

IntersectionVertexFilter::IntersectionVertexFilter(const std::vector<VertexFilter*>& filters):
	filters(filters)
{
}

bool IntersectionVertexFilter::isIncluded(const Vertex&v) const
{
	for (auto& filter: filters)
	{
		if (!filter->isIncluded(v))
			return false;
	}
	return true;
}

IntersectionVertexFilter::~IntersectionVertexFilter()
{
    // FIXME: make sure all filters are deleted.
}

string IntersectionVertexFilter::str() const
{
    stringstream s;
    s << "\"intersects\": [";
    bool needsComma = false;
	for (auto& filter: filters)
    {
        if (needsComma)
            s << ", ";
        s << filter->str();
        needsComma = true;
    }
    s << "]";
    return s.str();
}
