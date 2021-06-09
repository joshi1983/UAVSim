#include "UAVSimBinaryFileExporter.hpp"
#include <fstream>
#include <iostream>
using namespace std;

UAVSimBinaryFileExporter::UAVSimBinaryFileExporter(): FileExporter("uavsim")
{

}

UAVSimBinaryFileExporter::~UAVSimBinaryFileExporter()
{
}

void UAVSimBinaryFileExporter::save(const GroupNode& groupNode, const string & filename) const
{
	// get triangles.
	vector<Triangle> triangles = groupNode.getTriangles();
	ofstream out(filename, ios::out | ios::binary);
    if(!out) {
        cerr << "Cannot open file!" << filename << endl;
        throw exception();
    }
    float coordinates[3];
    if (sizeof(float) != 4)
    {
        cerr << "Unable to save file because we can not generate the required format." << endl;
        cerr << "float expected to be 4 bytes but is " << sizeof(float) << endl;
        throw exception();
    }
    for (vector<Triangle>::const_iterator it = triangles.begin(); it != triangles.end(); it++)
    {
        for (unsigned int vertexIndex = 0; vertexIndex < 3; vertexIndex++) {
            const Vertex & v = it->vertices[vertexIndex];
            coordinates[0] = v.p.x;
            coordinates[1] = v.p.y;
            coordinates[2] = v.p.z;
            out.write((char *) coordinates, sizeof(coordinates));
        }
    }
}
