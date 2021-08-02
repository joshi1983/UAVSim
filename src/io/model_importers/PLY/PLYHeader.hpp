#ifndef PLY_HEADER_HEADER_INCLUDED
#define PLY_HEADER_HEADER_INCLUDED
#include "PLYElement.hpp"
#include <fstream>
#include <vector>
#include <string>
#include "PLYFormat.hpp"

class PLYHeader
{
	public:
	    PLYHeader();
		PLYFormat format;
		std::vector<PLYElement> elements;
		std::vector<std::string> validate() const;
		std::string str() const;
		static PLYHeader parse(std::fstream & in);
};

#endif
