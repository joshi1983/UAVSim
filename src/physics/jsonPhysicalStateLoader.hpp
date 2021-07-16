#ifndef JSON_PHYSICAL_STATE_LOADER_HEADER_INCLUDED
#define JSON_PHYSICAL_STATE_LOADER_HEADER_INCLUDED
#include "../io/config/UAVSimConfig.hpp"
#include "PropellerMotorPhysicalState.hpp"

void loadPhysicalStateFromJSON(UAVSimConfig & uavConfig);
void loadPhysicalStateFromJSONObject(rapidjson::Value & input, PropellerMotorPhysicalState & result);

#endif
