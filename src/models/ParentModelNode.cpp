#include "ParentModelNode.hpp"

void ParentModelNode::copyChildren(ParentModelNode & result) const
{
    result.children.insert(result.children.end(), children.begin(), children.end());
}
