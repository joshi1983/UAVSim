#ifndef XML_UTILS_HEADER
#define XML_UTILS_HEADER

#include "../lib/TinyXml/tinyxml.h"
#include <string>

class XmlUtils
{
	public:
		static const TiXmlElement *getChildElementWithTagName(const TiXmlElement * e, const char * tagNames);
};

#endif
