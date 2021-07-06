#ifndef BATTERY_HEADER_INCLUDED
#define BATTERY_HEADER_INCLUDED
#include "Device.hpp"

class Battery: public Device
{
	public:
		virtual std::string getTypeName() const;
		virtual ~Battery();
		double voltage;
		double massKG;
};

#endif