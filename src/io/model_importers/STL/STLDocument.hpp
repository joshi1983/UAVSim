#ifndef STL_DOCUMENT_HEADER_INCLUDED
#define STL_DOCUMENT_HEADER_INCLUDED
#include <vector>
#include <fstream>
#include "STLFacet.hpp"
#include "STLHeader.hpp"

class STLDocument
{
	public:
		STLHeader header;
		std::vector<STLFacet> facets;
		void loadFrom(std::fstream & in);
};

#endif