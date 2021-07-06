#include "jsonDeviceFactory.hpp"
#include "../io/JsonUtils.hpp"
#include "Camera.hpp"
#include "PropellerMotor.hpp"
#include "ServoMotor.hpp"
#include "IMUSensor.hpp"
#include "Battery.hpp"
#include "../models/Vector3D.hpp"
using namespace std;

void loadDeviceProperties(rapidjson::Value::ValueIterator &itr, Device* device)
{
	device->name = (*itr)["name"].GetString();
	if (itr->HasMember("image-url") && (*itr)["image-url"].IsString())
        device->imageURL = (*itr)["image-url"].GetString();
	if (itr->HasMember("spec-url") && (*itr)["spec-url"].IsString())
        device->specSheetURL = (*itr)["spec-url"].GetString();
	if (itr->HasMember("position") && (*itr)["position"].IsObject())
		jsonObjectToVector3D((*itr)["position"], device->position);
}

Camera* createCamera(rapidjson::Value::ValueIterator &itr)
{
	Camera * cam = new Camera();
	loadDeviceProperties(itr, cam);
	if (itr->HasMember("rotation"))
	{
		jsonObjectToVector3D((*itr)["rotation"], cam->rotationAxis);
		cam->rotationAngle = (*itr)["rotation"]["angle"].GetDouble();
	}
	return cam;
}

PropellerMotor* createPropellerMotor(rapidjson::Value::ValueIterator &itr)
{
	PropellerMotor * motor = new PropellerMotor();
	loadDeviceProperties(itr, motor);
    motor->newtonsOfThrustAtOneRotationPerSecond = 1;
	if (itr->HasMember("newtonsOfThrustAtOneRotationPerSecond"))
        motor->newtonsOfThrustAtOneRotationPerSecond = (*itr)["newtonsOfThrustAtOneRotationPerSecond"].GetDouble();
	if (itr->HasMember("newtonMetersOfTorqueAtOneRotationPerSecond"))
        motor->newtonMetersOfTorqueAtOneRotationPerSecond = (*itr)["newtonMetersOfTorqueAtOneRotationPerSecond"].GetDouble();
	return motor;
}

ServoMotor* createServoMotor(rapidjson::Value::ValueIterator &itr)
{
	ServoMotor * motor = new ServoMotor();
	loadDeviceProperties(itr, motor);
    if (itr->HasMember("range") && itr->IsObject())
    {
        rapidjson::Value& range = (*itr)["range"];
        if (range.HasMember("max-degrees") && range["max-degrees"].IsNumber())
            motor->maxAngleDegrees = range["max-degrees"].GetDouble();
        if (range.HasMember("min-degrees") && range["min-degrees"].IsNumber())
            motor->minAngleDegrees = range["min-degrees"].GetDouble();
    }

	return motor;
}

IMUSensor* createIMUSensor(rapidjson::Value::ValueIterator &itr)
{
	IMUSensor * imu = new IMUSensor();
	loadDeviceProperties(itr, imu);
	return imu;
}

Battery* createBattery(rapidjson::Value::ValueIterator &itr)
{
	Battery * battery = new Battery();
	loadDeviceProperties(itr, battery);
	if (itr->HasMember("voltage") && (*itr)["voltage"].IsNumber())
        battery->voltage = (*itr)["voltage"].GetDouble();
	return battery;
}

Device* createDevice(rapidjson::Value::ValueIterator &itr)
{
	if (itr->HasMember("type"))
	{
		std::string type = (*itr)["type"].GetString();
		if (type == "camera")
			return createCamera(itr);
		else if (type == "propeller-motor")
			return createPropellerMotor(itr);
		else if (type == "servo-motor")
			return createServoMotor(itr);
		else if (type == "imu-sensor")
			return createIMUSensor(itr);
		else if (type == "battery")
			return createBattery(itr);
	}
	return nullptr;
}
