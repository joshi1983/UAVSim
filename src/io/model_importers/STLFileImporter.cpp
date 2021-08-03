#include "STLFileImporter.hpp"
#include "STL/STLDocument.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include "../../models/LeafNode.hpp"

using namespace std;

STLFileImporter::STLFileImporter(): FileImporter("stl")
{

}

STLFileImporter::~STLFileImporter()
{

}

GroupNode* STLFileImporter::load(const std::string & filename) const
{
	fstream in;
	in.open(filename, ios::in | ios::binary);
	STLDocument doc;
	doc.loadFrom(in);
	in.close();

	vector<Triangle> triangles;
	for (unsigned int i = 0; i < doc.facets.size(); i++)
	{
		triangles.push_back(Triangle());
		STLFacet & f = doc.facets[i];
		Triangle & t = triangles[triangles.size() - 1];
		for (unsigned int j = 0; j < 3; j++)
		{
			t.vertices[j].p = f.vertices[j];
		}
	}

    GroupNode* result = new GroupNode();
    LeafNode * leaf = new LeafNode();
    leaf->triangles = triangles;
    result->children.push_back(leaf);
    return result;
}
