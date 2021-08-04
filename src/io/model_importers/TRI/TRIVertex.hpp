#ifndef TRI_VERTEX_HEADER_INCLUDED
#define TRI_VERTEX_HEADER_INCLUDED
#include "../../../models/Vector3D.hpp"
#include "../../../models/Colour.hpp"
#include <string>

class TRIVertex
{
	public:
		void loadFromLine(const std::string& line);
		Vector3D position;
		Vector3D normal;
		Colour colour;
};

#endif