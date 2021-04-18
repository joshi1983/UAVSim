#ifndef PARENT_MODEL_NODE_HPP
#define PARENT_MODEL_NODE_HPP
#include "ModelNode.hpp"

class ParentModelNode: public ModelNode
{
    protected:
        void copyChildren(ParentModelNode & result) const;
	public:
		std::vector<ModelNode*> children;

};

#endif
