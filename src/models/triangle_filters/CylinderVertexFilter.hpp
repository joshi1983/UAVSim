#ifndef CYLINDER_VERTEX_FILTER_HEADER_INCLUDED
#define CYLINDER_VERTEX_FILTER_HEADER_INCLUDED
#include "VertexFilter.hpp"

class CylinderVertexFilter: public VertexFilter
{
	private:
		Vertex position;
		double radius;
		double dx, dy, dz;
	public:
		CylinderVertexFilter(double radius, double px, double py, double pz, double dx, double dy, double dz);
		virtual bool isIncluded(const Vertex&v) const override;
};

#endif
