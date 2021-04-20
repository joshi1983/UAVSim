#include "ParentModelNode.hpp"

void ParentModelNode::copyChildren(ParentModelNode & result) const
{
    result.children.insert(result.children.end(), children.begin(), children.end());
}

ParentModelNode::~ParentModelNode()
{
    for (auto child = children.begin(); child != children.end(); child++)
    {
        delete *child;
    }
}
