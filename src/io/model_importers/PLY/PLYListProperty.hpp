#ifndef PLY_LIST_PROPERTY_HEADER_INCLUDED
#define PLY_LIST_PROPERTY_HEADER_INCLUDED
#include <string>
#include "PLYDataTypes.hpp"
#include "PLYProperty.hpp"

class PLYListProperty: public PLYProperty
{
	public:
		PLYListProperty(const std::string & name, PLYDataTypes::PLYType lengthType, PLYDataTypes::PLYType listElementType);
		PLYDataTypes::PLYType lengthType;
		PLYDataTypes::PLYType listElementType;
		virtual std::string str() const;
		static PLYListProperty* parse(const std::string & line);
};

#endif
