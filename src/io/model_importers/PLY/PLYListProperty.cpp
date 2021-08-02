#include "PLYListProperty.hpp"
#include <string>
#include "../../stringUtils.hpp"
#include <vector>
using namespace std;

PLYListProperty::PLYListProperty(const string & name, PLYDataTypes::PLYType lengthType,
PLYDataTypes::PLYType listElementType):
	PLYProperty(name, PLYDataTypes::PLYType::list), lengthType(lengthType), listElementType(listElementType)
{

}

PLYListProperty* PLYListProperty::parse(const string & line)
{
	string sanitizedLine = toLower(simplifyWhitespaces(trim(line)));
	vector<string> parts;
	tokenize(sanitizedLine, ' ', parts);
	string name = parts[4];
	PLYDataTypes::PLYType lengthType = PLYDataTypes::getFromName(parts[2]);
	PLYDataTypes::PLYType listElementType = PLYDataTypes::getFromName(parts[3]);
	return new PLYListProperty(name, lengthType, listElementType);
}

string PLYListProperty::str() const
{
    return string("property list ") + PLYDataTypes::getNameFor(lengthType) + string(" ")
        + PLYDataTypes::getNameFor(listElementType) + string(" ") + name;
}
