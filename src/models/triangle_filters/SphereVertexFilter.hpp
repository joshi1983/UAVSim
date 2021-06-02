#ifndef SPHERE_VERTEX_FILTER_HEADER_INCLUDED
#define SPHERE_VERTEX_FILTER_HEADER_INCLUDED
#include "VertexFilter.hpp"

class SphereVertexFilter: public VertexFilter
{
	private:
		double cx, cy, cz, radius;
	public:
		SphereVertexFilter(double cx, double cy, double cz, double radius);
		virtual bool isIncluded(const Vertex&v) const override;
};

#endif
