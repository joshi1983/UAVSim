#include "TRITriangle.hpp"
#include <sstream>
#include <iostream>
using namespace std;

void TRITriangle::loadFromLine(const string& line, const vector<TRIVertex> & vertices)
{
	stringstream in(line);
	for (unsigned int i = 0; i < 3; i++)
	{
		int index;
		in >> index;
		if (index < 0 || index >= (int)vertices.size())
			cerr << "TRI vertex index(" << index << ") out of range 0.." << (vertices.size() - 1) << endl;
		else
			this->vertices[i] = vertices[index];
		if (i < 2 && in.eof())
		{
			cerr << "Expected 3 vertex indexes in line: " << line << endl;
			break;
		}
	}
}
