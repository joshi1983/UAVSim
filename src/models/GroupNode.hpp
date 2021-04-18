#ifndef GROUP_NODE_HPP
#define GROUP_NODE_HPP
#include "ParentModelNode.hpp"

class GroupNode: public ParentModelNode
{
	public:
		virtual ModelNode* clone() const override;
		virtual std::vector<Triangle> getTriangles() const override;
};

#endif
