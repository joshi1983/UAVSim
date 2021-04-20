#ifndef MODEL_NODE_HPP
#define MODEL_NODE_HPP
#include "Triangle.hpp"
#include <vector>

class ModelNode
{
	public:
	    virtual ~ModelNode();
		virtual ModelNode* clone() const = 0;
		virtual std::vector<Triangle> getTriangles() const = 0;
};

#endif
