#include "physics_api_handlers.hpp"
#include "../../JsonUtils.hpp"
#include "../../../physics/UAVPhysicalState.hpp"
#include "../../../physics/jsonPhysicalStateLoader.hpp"
#include "../../../devices/DeviceJsonSerializer.hpp"
#include "../../../models/animation/DefaultAnimation.hpp"
#include "../../../physics/PhysicalStateJsonSerializer.hpp"
#include <iostream>

using namespace std;

string getAllPhysicsData()
{
    UAVPhysicalState * uavState = UAVPhysicalState::getInstance();
    rapidjson::Document doc;
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
    toJSONValue(*uavState, doc, allocator);

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
            else
            {
                cerr << "Unable to find device with name: " << name << endl;
            }
        }
    }

    return string("{}");
}
