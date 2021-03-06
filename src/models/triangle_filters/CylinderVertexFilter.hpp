#ifndef CYLINDER_VERTEX_FILTER_HEADER_INCLUDED
#define CYLINDER_VERTEX_FILTER_HEADER_INCLUDED
#include "VertexFilter.hpp"

class CylinderVertexFilter: public VertexFilter
{
	private:
		Vector3D position;
		double radius;
		Vector3D direction;
	public:
		CylinderVertexFilter(double radius, double px, double py, double pz, double dx, double dy, double dz);
		virtual bool isIncluded(const Vertex&v) const override;
		virtual std::string str() const override;
};

#endif
