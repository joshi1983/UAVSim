#include "PLYProperty.hpp"
#include <iostream>
using namespace std;


PLYProperty::PLYProperty(const std::string & name, PLYDataTypes::PLYType dataType):
	name(name), dataType(dataType)
{

}

long int PLYProperty::readInt(fstream & in, PLYFormat format) const
{
	return PLYDataTypes::readInt(in, dataType, format);
}

double PLYProperty::readDouble(fstream & in, PLYFormat format) const
{
	return PLYDataTypes::readDouble(in, dataType, format);
}

string PLYProperty::str() const
{
    return string("property ") + PLYDataTypes::getNameFor(dataType) + string(" ") + name;
}
