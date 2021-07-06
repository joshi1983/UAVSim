#include "Devices.hpp"
#include "../io/config/Config.hpp"
#include "../lib/rapidjson/pointer.h"
#include "jsonDeviceFactory.hpp"
#include <iostream>
using namespace std;

Devices *Devices::main = nullptr;

void Devices::loadFromConfig()
{
    UAVSimConfig c;
    c.load(UAVSimConfig::config.getDefaultedString("/uav", "uav.json"));
    rapidjson::Value* a =  rapidjson::Pointer("/devices").Get(c.doc);
    if (a != nullptr && a->IsArray())
    {
        // loop through devices.
        for (rapidjson::Value::ValueIterator itr = a->Begin(); itr != a->End(); ++itr)
        {
			Device * device = createDevice(itr);
			if (device != nullptr)
				devices.push_back(device);
        }
    }
}

Devices::Devices()
{
	loadFromConfig();
}

Devices * Devices::getInstance()
{
    if (main == nullptr)
        main = new Devices();
    return main;
}

vector<Device*> Devices::getDevices()
{
    return devices;
}
