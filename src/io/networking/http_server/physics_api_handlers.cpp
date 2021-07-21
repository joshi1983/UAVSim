#include "physics_api_handlers.hpp"
#include "../../JsonUtils.hpp"
#include "../../../physics/UAVPhysicalState.hpp"
#include "../../../physics/jsonPhysicalStateLoader.hpp"
#include "../../../devices/DeviceJsonSerializer.hpp"
#include "../../../models/animation/DefaultAnimation.hpp"
#include <iostream>

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

string getAllPhysicsData()
{
    UAVPhysicalState * uavState = UAVPhysicalState::getInstance();
    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
    doc.AddMember("massKG", rapidjson::Value().SetDouble(uavState->massKG), allocator);
    doc.AddMember("pitchDegrees", rapidjson::Value().SetDouble(uavState->pitchDegrees), allocator);
    doc.AddMember("rollDegrees", rapidjson::Value().SetDouble(uavState->rollDegrees), allocator);
    doc.AddMember("yawDegrees", rapidjson::Value().SetDouble(uavState->yawDegrees), allocator);

    rapidjson::Value v;
    vector3DToRapidJsonObject(uavState->acceleration, v, allocator);
    doc.AddMember("acceleration", v, allocator);
    vector3DToRapidJsonObject(uavState->velocity, v, allocator);
    doc.AddMember("velocity", v, allocator);
    vector3DToRapidJsonObject(uavState->displacement, v, allocator);
    doc.AddMember("displacement", v, allocator);
    rapidjson::Value propellers;
    propellers.SetArray();
    for (auto propeller: uavState->propellerMotors)
    {
        propellerMotorToJSONValue(propeller, v, allocator);
        propellers.PushBack(v, allocator);
    }
    doc.AddMember("devices", propellers, allocator);

	string result;
	rapidJsonDocumentToString(doc, result);
	return result;
}

string handleAPIPostPhysicsTimeChangeRequest(rapidjson::Document &doc)
{
    double timeDeltaSeconds = getDefaultedDouble(doc, "seconds", 0.01);
    UAVPhysicalState * uavState = UAVPhysicalState::getInstance();
    uavState->simulateTimeChange(timeDeltaSeconds);
    AnimationState newState;
    DefaultAnimation::getInstance()->getState(0, newState);
    uavState->copyInto(newState);
    DefaultAnimation::getInstance()->setAnimationState(newState);
    return string("{}");
}

string handleAPIPostPhysicsRequest(rapidjson::Document &doc)
{
    UAVPhysicalState * uavState = UAVPhysicalState::getInstance();
    if (doc.HasMember("acceleration") && doc["acceleration"].IsObject())
        jsonObjectToVector3D(doc["acceleration"], uavState->acceleration);
    if (doc.HasMember("velocity") && doc["velocity"].IsObject())
        jsonObjectToVector3D(doc["velocity"], uavState->velocity);
    if (doc.HasMember("displacement") && doc["displacement"].IsObject())
        jsonObjectToVector3D(doc["displacement"], uavState->displacement);
    uavState->pitchDegrees = getDefaultedDouble(doc, "pitchDegrees", uavState->pitchDegrees);
    uavState->rollDegrees = getDefaultedDouble(doc, "rollDegrees", uavState->rollDegrees);
    uavState->yawDegrees = getDefaultedDouble(doc, "yawDegrees", uavState->yawDegrees);
    if (doc.HasMember("devices") && doc["devices"].IsArray())
    {
        rapidjson::Value& a = doc["devices"];
        for (rapidjson::Value::ValueIterator itr = a.Begin(); itr != a.End(); ++itr)
        {
            string name = (*itr)["device"]["name"].GetString();
            PropellerMotorPhysicalState * motor = uavState->getDeviceByName(name);
            if (motor != nullptr)
            {
                loadPhysicalStateFromJSONObject(*itr, *motor);
            }
        }
    }

    return string("{}");
}
