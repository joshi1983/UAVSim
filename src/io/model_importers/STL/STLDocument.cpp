#include "STLDocument.hpp"
#include <sstream>
#include "../../stringUtils.hpp"
#include "../../Files.hpp"
#include <iostream>
using namespace std;

void readVector3D(fstream &in, Vector3D & result)
{
	if (sizeof(float) == 4)
	{
		float components[3];
		in.read((char*)components, 12);
		result.x = components[0];
		result.y = components[1];
		result.z = components[2];
	}
	else if (sizeof(double) == 4)
	{
		double components[3];
		in.read((char*)components, 12);
		result.x = components[0];
		result.y = components[1];
		result.z = components[2];
	}
	else
		cerr << "Unable to find floating point type of byte count 4." << endl;
}

void STLDocument::loadFrom(fstream & in)
{
	if (STLHeader::isBinary(in))
	{
		// read up to 80 bytes in.
		char headerBuf[80];
		in.read(headerBuf, 80);
		header.text = headerBuf;
		uint32_t fCount;
		in.read((char*)(&fCount), 4);
		// loop loading facets until end of file is reached.
		for (unsigned int fIndex = 0; fIndex < fCount && !in.eof(); fIndex++)
		{
			facets.push_back(STLFacet());
			STLFacet& facet = facets[facets.size() - 1];
			readVector3D(in, facet.normal);
			for (unsigned short i = 0; i < 3; i++)
			{
				readVector3D(in, facet.vertices[i]);
			}
			in.read((char*)(&facet.attributes), 2);
		}
	}
	else
	{
		string line;
		getline(in, line);
		// chop off the first "solid" and store the rest.
		header.text = trim(line.substr(5));
		while (!in.eof())
		{
			facets.push_back(STLFacet());
			STLFacet& facet = facets[facets.size() - 1];

			{
			    getline(in, line);
			    line = trim(line);
			    if (line == "") // if the file ends with a blank line:
                {
                    facets.pop_back(); // remove the last facet.
                    break;
                }
				stringstream lineStream(line);
				string temp;
				lineStream >> temp; // should be "facet"
			    if (lineStream.eof() || temp != "facet")
                {
                    facets.pop_back();
                    break;
                }
				lineStream >> temp; // should be "normal".
				readVector3DAscii(lineStream, facet.normal);
				getline(in, line); // read "outer loop".
				if (line.find("loop") == string::npos)
                    cerr << "outer loop expected but got: " << line << endl;
			}
			for (unsigned short i = 0; i < 3; i++)
			{
				getline(in, line);
				stringstream lineStream(line);
				string vertexWord;
				lineStream >> vertexWord; // ignore.
				if (vertexWord != "vertex")
					cerr << "Expected the word vertex but got " << vertexWord << endl;
				readVector3DAscii(lineStream, facet.vertices[i]);
			}
			do {
				getline(in, line);
			} while (!in.eof() && line.find("endfacet") == string::npos);
		}
	}
}
