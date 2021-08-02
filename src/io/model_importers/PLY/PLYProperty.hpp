#ifndef PLY_PROPERTY_HEADER_INCLUDED
#define PLY_PROPERTY_HEADER_INCLUDED
#include "PLYDataTypes.hpp"
#include <string>
#include <fstream>
#include "PLYFormat.hpp"

class PLYProperty
{
	public:
		PLYProperty(const std::string & name, PLYDataTypes::PLYType dataType);
		std::string name;
		PLYDataTypes::PLYType dataType;
		long int readInt(std::fstream & in, PLYFormat format) const;
		double readDouble(std::fstream & in, PLYFormat format) const;
		virtual std::string str() const;
};

#endif
