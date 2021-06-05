#ifndef CUBE_VERTEX_FILTER_HEADER_INCLUDED
#define CUBE_VERTEX_FILTER_HEADER_INCLUDED
#include "VertexFilter.hpp"

class CubeVertexFilter: public VertexFilter
{
	private:
		double minX, minY, minZ;
		double maxX, maxY, maxZ;
	public:
		CubeVertexFilter(double minX, double minY, double minZ,
			double maxX, double maxY, double maxZ);
		virtual bool isIncluded(const Vertex&v) const override;
		virtual std::string str() const override;
};

#endif
