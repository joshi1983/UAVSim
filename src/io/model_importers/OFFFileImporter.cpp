#include "OFFFileImporter.hpp"
#include "../../models/LeafNode.hpp"
#include "OBJFileImporter.hpp"
#include "../stringUtils.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

void getLoadableLinesOFF(fstream& f, vector<string>& lines)
{
	string line;
	while(getline(f, line)){ //read data from file object and put it into string.
		line = simplifyWhitespaces(OBJFileImporter::removeComment(line));
		if (line.length() < 5) // too short to be a loadable line.
			continue;
		lines.push_back(line);
	}
	f.close(); //close the file object.
}

void addTriangle(unsigned int v1, unsigned int v2, unsigned int v3, const vector<Vertex>& vertices, vector<Triangle> &triangles)
{
    if (v1 >= vertices.size())
    {
        cerr << "vertex index " << v1 << " out of range 0.." << vertices.size() << endl;
        return;
    }
    if (v2 >= vertices.size())
    {
        cerr << "vertex index " << v2 << " out of range 0.." << vertices.size() << endl;
        return;
    }
    if (v3 >= vertices.size())
    {
        cerr << "vertex index " << v3 << " out of range 0.." << vertices.size() << endl;
        return;
    }
    Triangle t;
    t.vertices[0] = vertices[v1];
    t.vertices[1] = vertices[v2];
    t.vertices[2] = vertices[v3];
    triangles.push_back(t);
}

void addTriangles(const vector<unsigned int>& indexes, const vector<Vertex>& vertices, vector<Triangle> &triangles)
{
    addTriangle(indexes[0], indexes[1], indexes[2], vertices, triangles);
    for (unsigned int vertexIndex = 3; vertexIndex < indexes.size(); vertexIndex++)
    {
        addTriangle(indexes[vertexIndex - 3], indexes[vertexIndex - 1], indexes[vertexIndex], vertices, triangles);
    }
}

OFFFileImporter::OFFFileImporter(): FileImporter("off")
{

}

OFFFileImporter::~OFFFileImporter()
{

}

GroupNode* OFFFileImporter::load(const string & filename) const
{
	fstream f;
	f.open(filename, ios::in);
	if (f.is_open()){   //checking whether the file is open
		// filter down to the useful lines.
		vector<string> lines;
		getLoadableLinesOFF(f, lines);
		if (lines.size() < 1) {
			cerr << "OFF file unexpectedly short.  Must contain at least 1 line." << endl;
			return nullptr;
		}
		vector<Vertex> vertices;
		unsigned int numVertices, numFaces;
		{
            vector<string> parts;
            tokenize(lines[0], ' ', parts);
            numVertices = (unsigned int)stoi(parts[0]);
            numFaces = (unsigned int)stoi(parts[1]);
		}
		for (unsigned int i = 1; i <= numVertices;i++)
		{
            vector<string> parts;
			tokenize(lines[i], ' ', parts);
			if (parts.size() == 3 || parts.size() == 4)
				vertices.push_back(Vertex(stod(parts[0]), stod(parts[1]), stod(parts[2])));
			else
				cerr << "Expected vertex line to have 3 or sometimes 4 parts but got: " << parts.size() << endl;
		}
		vector<Triangle> triangles;
		for (unsigned int i = numVertices + 1; i < numVertices + numFaces && i < lines.size(); i++)
		{
            vector<string> parts;
			tokenize(lines[i], ' ', parts);
			unsigned int numVertices2 = (unsigned int)stoi(parts[0]);
			// The - 4 is in case the r, g, b components of a colour are specified.
			if (numVertices2 < 3)
				cerr << "Face vertex count of " << numVertices2 << " is not even enough to make a triangle." << endl;
			else if (numVertices2 != parts.size() - 1 && numVertices2 != parts.size() - 4)
				cerr << "Face vertex count of " << numVertices2 << " does not match number of parts " << (parts.size() - 1) << endl;
			else
			{
				vector<unsigned int> indexes;
				for (unsigned int j = 1; j <= numVertices2 + 1; j++)
					indexes.push_back(stoi(parts[j]));
				addTriangles(indexes, vertices, triangles);
			}
		}
 		GroupNode* result = new GroupNode();
		LeafNode * leaf = new LeafNode();
		leaf->triangles = triangles;
		result->children.push_back(leaf);
		return result;
	}
	else
	{
		cerr << "File not found or unable to open file: " << filename << endl;
		return nullptr;
	}
}
