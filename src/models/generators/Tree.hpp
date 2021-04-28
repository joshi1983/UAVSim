#ifndef TREE_GENERATOR_HEADER_INCLUDED
#define TREE_GENERATOR_HEADER_INCLUDED
#include "MeshGenerator.hpp"

class Tree: public MeshGenerator
{
    public:
        Tree();
		virtual GroupNode * generate() const override;
};

#endif // TREE_GENERATOR_HEADER_INCLUDED
