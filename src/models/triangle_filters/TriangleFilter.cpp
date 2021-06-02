#include "TriangleFilter.hpp"

TriangleFilter::TriangleFilter(unsigned int minimumRequired, VertexFilter * vf):
    minimumRequired(minimumRequired), vf(vf)
{
}

bool TriangleFilter::isIncluded(const Triangle & t) const
{
	unsigned int filteredVertexCount = 0;
	for (unsigned int i = 0; i < 3; i++)
	{
		if (vf.isIncluded(t.vertices[i]))
			filteredVertexCount++;
	}
	return filteredVertexCount >= minimumRequired;
}

TriangleFilter::~TriangleFilter()
{
    delete vf;
}
