#include "ElementProcessors.hpp"
#include <map>
#include <cstring>
#include <sstream>
#include <iostream>
using namespace std;

typedef map<string, ModelNode*(*)(const TiXmlElement&)> nameFunctionMap;

void vertexCopy(Vertex & result, const vector<double>& values, unsigned int startIndex)
{
    result.x = values[startIndex];
    result.y = values[startIndex + 1];
    result.z = values[startIndex + 2];
}

void addTriangle(const vector<int>& indexes, unsigned int index1, int index2, int index3,
const vector<double>& values, vector<Triangle> &triangles)
{
    Triangle triangle;
    vertexCopy(triangle.vertices[0], values, index1 * 3);
    vertexCopy(triangle.vertices[1], values, index2 * 3);
    vertexCopy(triangle.vertices[2], values, index3 * 3);
    triangles.push_back(triangle);
}

void addTriangles(const vector<int>& indexes, unsigned int startIndex, unsigned int endIndex,
const vector<double>& values, vector<Triangle> &triangles)
{
    if (endIndex - startIndex < 3)
        return; // weird case.  Not enough vertices for even 1 triangle.

    addTriangle(indexes, indexes[startIndex], indexes[startIndex + 1], indexes[startIndex + 2], values, triangles);
    for (unsigned int vertexIndex = startIndex + 3; vertexIndex < endIndex; vertexIndex++)
    {
        addTriangle(indexes, indexes[vertexIndex - 3], indexes[vertexIndex - 1], indexes[vertexIndex], values, triangles);
    }
}

namespace X3D {
    ModelNode * getModelNodeFromElement(const TiXmlElement& element)
    {
        nameFunctionMap functions;
        functions["Separator"] = getModelNodeFromSeparator;
        functions["Transform"] = getModelNodeFromTransform;
		functions["IndexedFaceSet"] = getModelNodeFromIndexedFaceSet;
        string tagName = element.Value();
        nameFunctionMap::const_iterator func;
        func = functions.find(tagName);
        if (func != functions.end())
            return func->second(element);
        return getModelNodeFromGroup(element);
    }

	void addChildrenTo(const TiXmlElement& element, ParentModelNode & parentNode)
	{
		// loop through child elements.
		for (const TiXmlElement * child = element.FirstChildElement(); child != NULL; child = child->NextSiblingElement())
		{
			parentNode.children.push_back(getModelNodeFromElement(*child));
		}
	}

    LeafNode * createLeafNodeFrom(const TiXmlElement& indexedFaceSet, const TiXmlElement& coordinateElement)
    {
        vector<double> values;
        vector<int> indexes;
        loadNumbers(indexedFaceSet.Attribute("coordIndex"), indexes);
        loadNumbers(coordinateElement.Attribute("point"), values);
        LeafNode * result = new LeafNode();
        unsigned startIndex = 0;
        for (unsigned int i = 0; i < indexes.size(); i++)
        {
            if (indexes[i] < 0)
            {
                addTriangles(indexes, startIndex, i, values, result->triangles);
                startIndex = i + 1;
            }
        }
        addTriangles(indexes, startIndex, indexes.size(), values, result->triangles);
        return result;
    }

    void loadNumbers(const char * s, vector<double> &result)
    {
        stringstream ss(s);
        double d;
        while(ss >> d)
            result.push_back(d);
    }

	void loadNumbers(const char * s, vector<int> & result)
	{
        stringstream ss(s);
        int i;
        while(ss >> i)
            result.push_back(i);
	}
}
