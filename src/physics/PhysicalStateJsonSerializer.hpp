#ifndef PHYSICAL_STATE_JSON_SERIALIZER_HEADER_INCLUDED
#define PHYSICAL_STATE_JSON_SERIALIZER_HEADER_INCLUDED
#include "PropellerMotorPhysicalState.hpp"
#include "UAVPhysicalState.hpp"
#include "../lib/rapidjson/document.h"

void propellerMotorToJSONValue(const PropellerMotorPhysicalState & motor,
    rapidjson::Value& result, rapidjson::Document::AllocatorType& allocator);
void toJSONValue(const UAVPhysicalState & motor,
    rapidjson::Value& result, rapidjson::Document::AllocatorType& allocator);

#endif
