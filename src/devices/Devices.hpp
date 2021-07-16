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
	    Device* getByName(const std::string& name);
		static Devices * getInstance();
};

#endif
