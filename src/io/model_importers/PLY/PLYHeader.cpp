#include "PLYHeader.hpp"
#include <iostream>
#include <vector>
#include "../../stringUtils.hpp"
#include "PLYListProperty.hpp"
#include <sstream>
using namespace std;

bool containsPropertyName(const vector<PLYProperty*>& properties, const string& name)
{
    for (unsigned int i = 0; i < properties.size(); i++)
    {
        if (properties[i]->name == name)
            return true;
    }
    return false;
}

PLYFormat getFormatFromLine(const string& line)
{
    string sanitizedLine = toLower(line);
	if (sanitizedLine.find("ascii") != string::npos)
		return PLYFormat::Ascii;
	else if (sanitizedLine.find("binary") != string::npos)
	{
		if (sanitizedLine.find("big") == string::npos)
			return PLYFormat::BinaryLittleEndian;
		else
			return PLYFormat::BinaryBigEndian;
	}
	else
	{
		cerr << "Unrecognized PLY format in line: " << line << endl;
		cerr << "Assuming format to be ASCII" << endl;
		return PLYFormat::Ascii;
	}
}

string getNameFrom(const string& line)
{
	string::size_type i = line.rfind(' ');
	if (i == string::npos)
	{
		cerr << "Unable to find name from line: " << line << endl;
		return string();
	}
	else
		return string(line.c_str() + i + 1);
}

vector<string> PLYHeader::validate() const
{
    const PLYElement* face = nullptr;
    const PLYElement* vertex = nullptr;
    vector<string> messages;

    for (auto& element: elements)
    {
        if (element.name == "vertex")
        {
            if (vertex != nullptr)
                messages.push_back("More than one vertex element found.");
            vertex = &element;
        }
        else if (element.name == "face")
        {
            if (face != nullptr)
                messages.push_back("More than one face element found.");
            face = &element;
        }
    }
    if (face == nullptr)
        messages.push_back("face element not found");
    else
    {
        // check that the face element has a list property.
        // check that the face element has nothing other than a list property.
        // check that all properties of the list are kinds of integers.
        if (face->properties.size() < 1)
            messages.push_back("Expected at least 1 property in face element");
        else if (!containsPropertyName(face->properties, "vertex_indices"))
            messages.push_back("vertex_indices property must be in face element");
        else
        {

        }
    }
    if (vertex == nullptr)
        messages.push_back("vertex element not found");
    else
    {
        // check that the "vertex" element defines, x, y, z.
        if (vertex->properties.size() < 3)
            messages.push_back("vertex element should define x, y, z.  There are less than 3 properties.");
        if (!containsPropertyName(vertex->properties, "x"))
            messages.push_back("vertex element missing property x.");
        if (!containsPropertyName(vertex->properties, "y"))
            messages.push_back("vertex element missing property y.");
        if (!containsPropertyName(vertex->properties, "z"))
            messages.push_back("vertex element missing property z.");
    }

    return messages;
}

PLYHeader::PLYHeader(): format(PLYFormat::Ascii)
{

}

PLYHeader PLYHeader::parse(std::fstream & in)
{
	PLYHeader result;
	string line;
	// loop through lines from in.
	 while (getline(in, line, '\n')){
		 line = trim(line);
		 if (line.find("end_header") == 0)
            break;
		 else if (line.rfind("format", 0) == 0)
			 result.format = getFormatFromLine(toLower(line));
		 else if (line.rfind("element", 0) == 0)
		 {
			line = simplifyWhitespaces(line);
			vector<string> parts;
			tokenize(line, ' ', parts);
			if (parts.size() < 3)
			{
				cerr << "PLY element line must have 3 parts but found: " << parts.size() << " in line " << line << endl;
			}
			else {
				PLYElement element(parts[1], stoi(parts[2]));
				result.elements.push_back(element);
			}
		 }
		 else if (line.rfind("property", 0) == 0)
		 {
			 if (result.elements.size() == 0)
				 cerr << "Unable to process property line that is before an element.  line: " << line << endl;
			 else
			 {
				line = simplifyWhitespaces(line);
				// process property by pushing it to the last of result.elements.
				vector<string> parts;
				tokenize(line, ' ', parts);
				PLYElement& lastElement = result.elements[result.elements.size() - 1];
				if (toLower(parts[1]) == "list")
				{
					lastElement.properties.push_back(PLYListProperty::parse(line));
				}
				else
				{
					string name = parts[2];
					PLYDataTypes::PLYType type = PLYDataTypes::getFromName(parts[1]);
					lastElement.properties.push_back(new PLYProperty(name, type));
				}
			 }
		 }
		 else if (line.rfind("obj_info", 0) == 0)
		 {
			 // Do nothing.
			 // Some PLY files specify object information that appears to be vendor-specific.
		 }
    }

	return result;
}

string PLYHeader::str() const
{
    ostringstream result;
    result << "ply" << endl;
    result << "format ";
    if (format == PLYFormat::Ascii)
        result << "ascii";
    else if (format == PLYFormat::BinaryBigEndian)
        result << "binary_big_endian";
    else
        result << "binary_little_endian";
    result << " 1.0" << endl;
    for (unsigned int eIndex = 0; eIndex < elements.size(); eIndex++)
    {
        result << elements[eIndex].str();
    }
    result << "end_header" << endl;
    return result.str();
}
