#include "DeviceJsonSerializer.hpp"
#include "Camera.hpp"
#include "Battery.hpp"
#include "IMUSensor.hpp"
#include "ServoMotor.hpp"
#include "PropellerMotor.hpp"
#include "../io/JsonUtils.hpp"
#include <string>
using namespace std;

void convertDeviceToRapidJson(const Device* device, rapidjson::Value & result, rapidjson::Document::AllocatorType& allocator)
{
	result.SetObject();
	string type = device->getTypeName();
	result.AddMember("type", rapidjson::Value().SetString(type.c_str(), type.length(), allocator), allocator);
	result.AddMember("name", rapidjson::Value().SetString(device->name.c_str(), device->name.length(), allocator), allocator);
	result.AddMember("image-url", rapidjson::Value().SetString(device->imageURL.c_str(), device->imageURL.length(), allocator), allocator);
	result.AddMember("spec-url", rapidjson::Value().SetString(device->specSheetURL.c_str(), device->specSheetURL.length(), allocator), allocator);
	rapidjson::Value positionObject;
	vector3DToRapidJsonObject(device->position, positionObject, allocator);
	result.AddMember("position", positionObject, allocator);
	if (type == "camera")
	{
		const Camera*cam = (Camera*)device;
		rapidjson::Value rotationObject;
		vector3DToRapidJsonObject(cam->rotationAxis, rotationObject, allocator);
		rotationObject.AddMember("rotationAngle", rapidjson::Value().SetDouble(cam->rotationAngle), allocator);
		result.AddMember("rotation", rotationObject, allocator);
	}
	else if (type == "servo-motor")
	{
		const ServoMotor* servo = (ServoMotor*)device;
		rapidjson::Value rangeObject;
		rangeObject.SetObject();
		rangeObject.AddMember("max-degrees", rapidjson::Value().SetDouble(servo->maxAngleDegrees), allocator);
		rangeObject.AddMember("min-degrees", rapidjson::Value().SetDouble(servo->minAngleDegrees), allocator);
		result.AddMember("range", rangeObject, allocator);
	}
	else if (type == "propeller-motor")
	{
		const PropellerMotor* motor = (PropellerMotor*)device;
		rapidjson::Value physicsObject;
		physicsObject.SetObject();
		physicsObject.AddMember("newtonsOfThrustAtOneRotationPerSecond", rapidjson::Value().SetDouble(motor->newtonsOfThrustAtOneRotationPerSecond), allocator);
		physicsObject.AddMember("newtonMetersOfTorqueAtOneRotationPerSecond", rapidjson::Value().SetDouble(motor->newtonMetersOfTorqueAtOneRotationPerSecond), allocator);
		result.AddMember("physics", physicsObject, allocator);
	}
}
