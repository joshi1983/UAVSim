#include "UAVSimBinaryFileExporter.hpp"
#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;

UAVSimBinaryFileExporter::UAVSimBinaryFileExporter(): FileExporter("uavsim")
{

}

UAVSimBinaryFileExporter::~UAVSimBinaryFileExporter()
{
}

void UAVSimBinaryFileExporter::write(const vector<Triangle>& triangles, vector<unsigned char> & out)
{
    float coordinates[3];
    if (sizeof(float) != 4)
    {
        cerr << "Unable to save file because we can not generate the required format." << endl;
        cerr << "float expected to be 4 bytes but is " << sizeof(float) << endl;
        throw exception();
    }
    unsigned char buffer[sizeof(float)*3];
    for (vector<Triangle>::const_iterator it = triangles.begin(); it != triangles.end(); it++)
    {
        for (unsigned int vertexIndex = 0; vertexIndex < 3; vertexIndex++) {
            const Vertex & v = it->vertices[vertexIndex];
            coordinates[0] = v.p.x;
            coordinates[1] = v.p.y;
            coordinates[2] = v.p.z;
            memcpy(buffer, coordinates, sizeof(buffer));
            for (unsigned int i = 0; i < sizeof(float) * 3; i++)
                out.push_back(buffer[i]);
        }
    }
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
    vector<unsigned char> outMemory;
	UAVSimBinaryFileExporter::write(triangles, outMemory);
	for (unsigned int i = 0; i < outMemory.size(); i++)
        out << outMemory[i];
    out.close();
}
