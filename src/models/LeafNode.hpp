#ifndef LEAF_NODE_HEADER
#define LEAF_NODE_HEADER
#include "ModelNode.hpp"

class LeafNode: public ModelNode
{
	public:
		std::vector<Triangle> triangles;
		virtual ModelNode* clone() const override;
		virtual std::vector<Triangle> getTriangles() const override;
};

#endif
