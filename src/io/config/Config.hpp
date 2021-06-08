#ifndef _CONFIG765_HEADER_INCLUDED_
#define _CONFIG765_HEADER_INCLUDED_
#include "../../lib/rapidjson/document.h"
#include <iostream>
#include <string>

class UAVSimConfig
{
	public:
	    UAVSimConfig();
	    rapidjson::Document doc;
		void load(const std::string & filename);
		void load();
        bool getDefaultedBool(std::string path, bool defaultedValue);
        double getDefaultedDouble(std::string path, double defaultedValue);
        std::string getDefaultedString(std::string path, std::string defaultedValue);
        static UAVSimConfig config;
};

#endif
