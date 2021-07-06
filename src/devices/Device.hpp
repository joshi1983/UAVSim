#ifndef DEVICE_HEADER_INCLUDED
#define DEVICE_HEADER_INCLUDED
#include <string>
#include "../models/Vector3D.hpp"

class Device
{
	public:
	    virtual std::string getTypeName() const = 0;
	    std::string specSheetURL;
	    std::string imageURL;
		std::string name;
		Vector3D position;
		virtual ~Device();
};

#endif
