#ifndef MESH_GENERATOR_HEADER_INCLUDED
#define MESH_GENERATOR_HEADER_INCLUDED
#include "../GroupNode.hpp"

class MeshGenerator
{
	public:
		virtual GroupNode * generate() const = 0;
};

#endif