#include "LeafNode.hpp"
using namespace std;

ModelNode* LeafNode::clone() const
{
    LeafNode* result = new LeafNode();
    result->triangles.insert(result->triangles.end(), triangles.begin(), triangles.end());
    return result;
}

vector<Triangle> LeafNode::getTriangles() const
{
    return this->triangles;
}
