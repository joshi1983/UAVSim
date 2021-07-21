#include "PhysicalStateJsonSerializer.hpp"
#include "../devices/DeviceJsonSerializer.hpp"
#include "../io/JsonUtils.hpp"
#include "../lib/rapidjson/pointer.h"
using namespace std;

void propellerMotorToJSONValue(const PropellerMotorPhysicalState & motor,
    rapidjson::Value& result, rapidjson::Document::AllocatorType& allocator)
{
    result.SetObject();
    result.AddMember("bladeAccelerationDegreesPerSecondPerSecond", rapidjson::Value().SetDouble(motor.bladeAccelerationDegreesPerSecondPerSecond), allocator);
    result.AddMember("bladeRotationSpeedDegreesPerSecond", rapidjson::Value().SetDouble(motor.bladeRotationSpeedDegreesPerSecond), allocator);
    result.AddMember("bladeAngleDegrees", rapidjson::Value().SetDouble(motor.bladeAngleDegrees), allocator);

    rapidjson::Value deviceObject;
    convertDeviceToRapidJson(motor.motor, deviceObject, allocator);
    result.AddMember("device", deviceObject, allocator);
}

void toJSONValue(const UAVPhysicalState & uavState,
    rapidjson::Value& result, rapidjson::Document::AllocatorType& allocator)
{
    result.SetObject();
    result.AddMember("massKG", rapidjson::Value().SetDouble(uavState.massKG), allocator);
    result.AddMember("pitchDegrees", rapidjson::Value().SetDouble(uavState.pitchDegrees), allocator);
    result.AddMember("rollDegrees", rapidjson::Value().SetDouble(uavState.rollDegrees), allocator);
    result.AddMember("yawDegrees", rapidjson::Value().SetDouble(uavState.yawDegrees), allocator);

    rapidjson::Value v;
    vector3DToRapidJsonObject(uavState.acceleration, v, allocator);
    result.AddMember("acceleration", v, allocator);
    vector3DToRapidJsonObject(uavState.velocity, v, allocator);
    result.AddMember("velocity", v, allocator);
    vector3DToRapidJsonObject(uavState.displacement, v, allocator);
    result.AddMember("displacement", v, allocator);
    rapidjson::Value propellers;
    propellers.SetArray();
    for (const PropellerMotorPhysicalState& propeller: uavState.propellerMotors)
    {
        propellerMotorToJSONValue(propeller, v, allocator);
        propellers.PushBack(v, allocator);
    }
    result.AddMember("devices", propellers, allocator);
}
