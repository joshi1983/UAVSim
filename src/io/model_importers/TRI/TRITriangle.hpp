#ifndef TRI_TRIANGLE_HEADER_INCLUDED
#define TRI_TRIANGLE_HEADER_INCLUDED
#include "TRIVertex.hpp"
#include <vector>

class TRITriangle
{
	public:
		TRIVertex vertices[3];
		void loadFromLine(const std::string& line, const std::vector<TRIVertex> & vertices);
};

#endif