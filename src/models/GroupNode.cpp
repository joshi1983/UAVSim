#include "GroupNode.hpp"

using namespace std;

vector<Triangle> GroupNode::getTriangles() const
{
	vector<Triangle> result;
	for (vector<ModelNode*>::const_iterator i = this->children.begin(); i != this->children.end(); i++) {
        vector<Triangle> childTriangles = (*i)->getTriangles();
		result.insert(result.end(), childTriangles.begin(), childTriangles.end());
	}
	return result;
}

ModelNode* GroupNode::clone() const
{
	GroupNode * result = new GroupNode();
	this->copyChildren(*result);
	return result;
}
