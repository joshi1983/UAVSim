#include "TransformNode.hpp"

using namespace std;

vector<Triangle> TransformNode::getTriangles() const
{
	vector<Triangle> result;
	for (vector<ModelNode*>::const_iterator i = this->children.begin(); i != this->children.end(); i++) {
        vector<Triangle> childTriangles = (*i)->getTriangles();
		result.insert(result.end(), childTriangles.begin(), childTriangles.end());
	}

	// FIXME: perform transformation.

	return result;
}

ModelNode* TransformNode::clone() const
{
	TransformNode * result = new TransformNode();
	this->copyChildren(*result);
	// FIXME: copy transformation.

	return result;
}
