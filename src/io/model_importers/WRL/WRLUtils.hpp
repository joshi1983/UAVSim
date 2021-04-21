#ifndef WRL_UTILS_HEADER
#define WRL_UTILS_HEADER
#include "../../../lib/TinyXML/tinyxml.h"
#include <string>

TiXmlDocument * vrmlToX3DDocument(const std::string & content);

class InvalidVRMLElementNameException
{
    private:
        std::string msg;
	public:
		InvalidVRMLElementNameException(const std::string& msg);
		std::string what() const;
};

#endif
