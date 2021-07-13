#ifndef DEVICE_JSON_SERIALIZER_HEADER_INCLUDED
#define DEVICE_JSON_SERIALIZER_HEADER_INCLUDED
#include "Device.hpp"
#include "../lib/rapidjson/document.h"

void convertDeviceToRapidJson(const Device* device, rapidjson::Value & result, rapidjson::Document::AllocatorType& allocator);

#endif
