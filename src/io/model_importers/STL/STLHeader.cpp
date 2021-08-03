#include "STLHeader.hpp"
#include <cstring>
using namespace std;

bool STLHeader::isBinary(std::fstream & in)
{
	// does the file start with the word "solid"?
	char buf[6];
	in.read(buf, 5);
	buf[5] = '\0';
	in.seekg(0, in.beg);
	// STL files that start with "solid" are ASCII.
	if (strcmp(buf, "solid") == 0)
		return false;
	else
		return true;
}