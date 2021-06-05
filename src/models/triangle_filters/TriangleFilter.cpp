#include "TriangleFilter.hpp"
#include <iostream>
using namespace std;

TriangleFilter::TriangleFilter(unsigned int minimumRequired, VertexFilter * vf):
    minimumRequired(minimumRequired), vf(vf)
{
}

bool TriangleFilter::isIncluded(const Triangle & t) const
{
	unsigned int filteredVertexCount = 0;
	for (const Vertex & v: t.vertices)
	{
		if (vf->isIncluded(v))
			filteredVertexCount++;
	}
	return filteredVertexCount >= minimumRequired;
}

TriangleFilter::~TriangleFilter()
{
    delete vf;
}

void TriangleFilter::removeFrom(vector<Triangle> & triangles) const
{
    vector<Triangle> result;
    unsigned int originalSize = triangles.size();
    unsigned int count = 0;
    for (Triangle& triangle: triangles)
    {
        if (!isIncluded(triangle))
            result.push_back(triangle);
        else
            count++;
    }
    triangles = result;
    cerr << "Count = " << count << ".  old size is: " << originalSize << ".  new size is: " << triangles.size() << endl;
}

ostream& operator<<(ostream &strm, const TriangleFilter &tf)
{
    return strm << "TriangleFilter(" << tf.vf->str() << ")";
}
