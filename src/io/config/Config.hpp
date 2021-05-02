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
        static UAVSimConfig config;
};

#endif
