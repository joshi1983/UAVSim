#include "TRIFileImporter.hpp"
#include "TRI/TRIDocument.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include "../../models/LeafNode.hpp"

using namespace std;

TRIFileImporter::TRIFileImporter(): FileImporter("tri")
{

}

TRIFileImporter::~TRIFileImporter()
{

}

GroupNode* TRIFileImporter::load(const std::string & filename) const
{
	fstream in;
	in.open(filename, ios::in);
	TRIDocument doc;
	doc.loadFrom(in);
	in.close();

	vector<Triangle> triangles;
	for (unsigned int i = 0; i < doc.triangles.size(); i++)
	{
		triangles.push_back(Triangle());
		TRITriangle & tri = doc.triangles[i];
		Triangle & t = triangles[triangles.size() - 1];
		for (unsigned int j = 0; j < 3; j++)
		{
			t.vertices[j].p = tri.vertices[j].position;
		}
	}

    GroupNode* result = new GroupNode();
    LeafNode * leaf = new LeafNode();
    leaf->triangles = triangles;
    result->children.push_back(leaf);
    return result;
}
