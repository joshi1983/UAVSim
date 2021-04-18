#include "XmlUtils.hpp"
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

const TiXmlElement* XmlUtils::getChildElementWithTagName(const TiXmlElement * e, const char * tagNames)
{
    istringstream iss(tagNames);
    vector<string> tagNameStrings;
    string token;
    while (getline(iss, token, ',')){
        tagNameStrings.push_back(token);
    }
    for (const TiXmlElement * child = e->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
    {
        for (vector<string>::const_iterator it = tagNameStrings.begin(); it != tagNameStrings.end(); it++)
        {
            if (strcmp(child->Value(), it->c_str()) == 0)
                return child;
        }
    }
	return NULL;
}
