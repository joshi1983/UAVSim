#include "TRIDocument.hpp"
using namespace std;

void TRIDocument::loadFrom(fstream & in)
{
	int numVertices, numTriangles;
	in >> numVertices;
	in >> numTriangles;
	vector<TRIVertex> vertices;
	// loop through lines of file.
	for (int i = 0; !in.eof() && i < numVertices; i++)
	{
		string line;
		do
        {
            getline(in, line);
        } while (line == "" && !in.eof());
		vertices.push_back(TRIVertex());
		vertices[i].loadFromLine(line);
	}
	for (int i = 0; !in.eof() && i < numTriangles; i++)
	{
		string line;
		getline(in, line);
		triangles.push_back(TRITriangle());
		triangles[i].loadFromLine(line, vertices);
	}
}
