#ifndef _CONFIG765_HEADER_INCLUDED_
#define _CONFIG765_HEADER_INCLUDED_
#include "../../lib/rapidjson/document.h"
#include <iostream>

class UAVSimConfig
{
    private:
	    UAVSimConfig();
	public:
	    rapidjson::Document doc;
		void load();
        bool getDefaultedBool(std::string path, bool defaultedValue) const;
        double getDefaultedDouble(std::string path, double defaultedValue) const;
        static UAVSimConfig config;
};

#endif
