#ifndef TRI_DOCUMENT_HEADER_INCLUDED
#define TRI_DOCUMENT_HEADER_INCLUDED
#include <fstream>
#include "TRITriangle.hpp"

/*
Based on the TRI format as described at:
http://paulbourke.net/dataformats/tri/
*/
class TRIDocument
{
	public:
		void loadFrom(std::fstream & in);
		std::vector<TRITriangle> triangles;
};

#endif