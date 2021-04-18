#ifndef TRANSFORM_NODE_HPP
#define TRANSFORM_NODE_HPP
#include "ParentModelNode.hpp"

/*
Represents part of a scene graph allowing for many kinds of linear transformation.
These transformations will include:
- rotation around arbitrary axis
- translation
*/
class TransformNode: public ParentModelNode
{
	public:
		virtual ModelNode* clone() const override;
		virtual std::vector<Triangle> getTriangles() const override;
};

#endif
