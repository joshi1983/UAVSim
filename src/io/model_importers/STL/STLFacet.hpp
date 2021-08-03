#ifndef STL_FACET_HEADER_INCLUDED
#define STL_FACET_HEADER_INCLUDED
#include "../../../models/Vector3D.hpp"

class STLFacet
{
	public:
		STLFacet();
		Vector3D normal;
		Vector3D vertices[3];
		int16_t attributes;
};

#endif
