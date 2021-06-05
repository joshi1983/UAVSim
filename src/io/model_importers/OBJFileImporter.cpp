#include "OBJFileImporter.hpp"
#include "../stringUtils.hpp"
#include "../../models/LeafNode.hpp"
#include <vector>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <iostream>
using namespace std;

string removeComment(const string& line)
{
	char * c = strchr(line.c_str(), '#');
	string result;
	if (c != nullptr)
	{
		result = line.substr(0, c - line.c_str());
	}
	else
        result = line;
	return trim(result);
}

void getLoadableLines(fstream& f, vector<string>& lines)
{
	string line;
	while(getline(f, line)){ //read data from file object and put it into string.
		line = simplifyWhitespaces(removeComment(line));
		if (line.length() < 4) // too short to be a loadable line.
			continue;
		// if not starting with "v " or "f ", continue.
		if (line.rfind("v ", 0) == 0 || line.rfind("f ", 0) == 0)
			lines.push_back(line);
	}
	f.close(); //close the file object.
}

int getVertexIndex(int index, int size)
{
    if (index < 0)
        return size + index;
    else
        return index - 1;
}

void addTriangle(int v1, int v2, int v3, const vector<Vertex>& vertices, vector<Triangle> &triangles)
{
    Triangle t;
    t.vertices[0] = Vertex(vertices[getVertexIndex(v1, vertices.size())]);
    t.vertices[1] = Vertex(vertices[getVertexIndex(v2, vertices.size())]);
    t.vertices[2] = Vertex(vertices[getVertexIndex(v3, vertices.size())]);
    triangles.push_back(t);
}

void addTriangles(const vector<int>& indexes, const vector<Vertex>& vertices, vector<Triangle> &triangles)
{
    addTriangle(indexes[0], indexes[1], indexes[2], vertices, triangles);
    for (unsigned int vertexIndex = 3; vertexIndex < indexes.size(); vertexIndex++)
    {
        addTriangle(indexes[vertexIndex - 3], indexes[vertexIndex - 1], indexes[vertexIndex], vertices, triangles);
    }
}

unsigned int getPositionVertexIndex(const string& s)
{
    const char * c = strchr(s.c_str(), '/');
    if (c != nullptr)
        return stoi(s.substr(0, c - s.c_str()));
    else
        return stoi(s);
}

OBJFileImporter::OBJFileImporter(): FileImporter("obj")
{

}

OBJFileImporter::~OBJFileImporter()
{
}

GroupNode* OBJFileImporter::load(const string & filename) const
{
    cerr << "OBJFileImporter load called." << endl;
	fstream f;
	f.open(filename, ios::in);
	if (f.is_open()){   //checking whether the file is open
		// filter down to the useful lines.
		vector<string> lines;
		getLoadableLines(f, lines);
		cerr << "Number of loadable lines: " << lines.size() << endl;
		vector<Vertex> vertices;
		for (string& line: lines)
		{
			if (line.rfind("v ", 0) == 0)
			{
				vector<string> parts;
				tokenize(line, ' ', parts);
				if (parts.size() > 3) {
					double x = stod(parts[1]);
					double y = stod(parts[2]);
					double z = stod(parts[3]);
					vertices.push_back(Vertex(x, y, z));
				}
			}
		}
		cerr << "Number of vertices: " << vertices.size() << endl;
		vector<Triangle> triangles;
		for (string& line: lines)
		{
			if (line.rfind("f ", 0) == 0)
			{
				// process face.
				vector<string> parts;
				tokenize(line, ' ', parts);
                vector<int> indexes;
                for (unsigned int i = 1; i < parts.size(); i++)
                    indexes.push_back(getPositionVertexIndex(parts[i]));
                addTriangles(indexes, vertices, triangles);
			}
		}
		cerr << "Number of triangles: " << triangles.size() << endl;
		GroupNode* result = new GroupNode();
		LeafNode * leaf = new LeafNode();
		leaf->triangles = triangles;
		result->children.push_back(leaf);
		return result;
	}
	else
    {
        cerr << "Unable to open " << filename << endl;
		throw exception();
    }
}
