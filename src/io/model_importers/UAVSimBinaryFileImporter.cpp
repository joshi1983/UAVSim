#include "UAVSimBinaryFileImporter.hpp"
#include "../../models/LeafNode.hpp"
#include <fstream>
#include <iostream>

using namespace std;

UAVSimBinaryFileImporter::UAVSimBinaryFileImporter(): FileImporter("uavsim")
{
}

UAVSimBinaryFileImporter::~UAVSimBinaryFileImporter()
{
}

GroupNode* UAVSimBinaryFileImporter::load(const string & filename) const
{
	ifstream in(filename, ios::in | ios::binary);
	if(!in) {
        cerr << "Cannot open file! " << filename << endl;
        throw exception();
    }
    if (sizeof(float) != 4)
    {
        cerr << "Cannot open file because float is not 4 bytes.  It is " << sizeof(float) << endl;
        throw exception();
    }
	float coordinates[3];
    vector<Triangle> triangles;
    Triangle triangle;
	for (unsigned int triangleIndex = 0; !in.eof(); triangleIndex++)
	{
        for (unsigned int vertexIndex = 0; vertexIndex < 3; vertexIndex++)
        {
            in.read((char*)coordinates, sizeof(coordinates));
            triangle.vertices[vertexIndex].p.x = coordinates[0];
            triangle.vertices[vertexIndex].p.y = coordinates[1];
            triangle.vertices[vertexIndex].p.z = coordinates[2];
        }
        triangles.push_back(triangle);
	}
	LeafNode * leaf = new LeafNode();
	leaf->triangles = triangles;
	GroupNode * result = new GroupNode();
	result->children.push_back(leaf);
	return result;
}
