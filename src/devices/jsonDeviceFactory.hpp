#ifndef JSON_DEVICE_FACTORY_HEADER_INCLUDED
#define JSON_DEVICE_FACTORY_HEADER_INCLUDED
#include "Device.hpp"
#include "../lib/rapidjson/document.h"

Device* createDevice(rapidjson::Value::ValueIterator &itr);

#endif