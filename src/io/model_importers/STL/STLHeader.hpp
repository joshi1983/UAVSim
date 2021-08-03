#ifndef STL_HEADER_HEADER_INCLUDED
#define STL_HEADER_HEADER_INCLUDED
#include <fstream>
#include <string>

class STLHeader
{
	public:
		std::string text;
		static bool isBinary(std::fstream & in);
};

#endif