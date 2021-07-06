#ifndef DEVICES_HEADER_INCLUDED
#define DEVICES_HEADER_INCLUDED
#include <vector>
#include "Device.hpp"

class Devices
{
	private:
	    std::vector<Device*> devices;
		void loadFromConfig();
		Devices();
		static Devices *main;
	public:
	    std::vector<Device*> getDevices();
		static Devices * getInstance();
};

#endif
