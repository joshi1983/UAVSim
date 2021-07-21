#include "PhysicsAPITest.hpp"
#include "../../io/networking/http_server/physics_api_handlers.hpp"
#include "../../physics/PropellerMotorPhysicalState.hpp"
#include "../../physics/UAVPhysicalState.hpp"
#include <string>
#include <iostream>
using namespace std;

void getPhysicsDocument(rapidjson::Document& doc)
{
	string body = getAllPhysicsData();
	doc.Parse<0>(std::string(body).data());
}

void testPhysicsHTTPGet(UnitTest& unitTest)
{
    rapidjson::Document doc;
	getPhysicsDocument(doc);
	unitTest.assertTrue(doc.IsObject(), "physics api should return an object.");
	unitTest.assertTrue(doc.HasMember("acceleration"), "physics api should return an object with key acceleration.");
	unitTest.assertTrue(doc.HasMember("velocity"), "physics api should return an object with key velocity.");
	unitTest.assertTrue(doc.HasMember("displacement"), "physics api should return an object with key displacement.");
	rapidjson::Value& acceleration = doc["acceleration"];
	unitTest.assertTrue(acceleration.HasMember("x"), "acceleration should have an x member");
	unitTest.assertTrue(acceleration.HasMember("y"), "acceleration should have an y member");
	unitTest.assertTrue(acceleration.HasMember("z"), "acceleration should have an z member");
}

void testAccelerationWriteAndRead(UnitTest& unitTest)
{
    rapidjson::Document originalStateDoc;
    getPhysicsDocument(originalStateDoc);

    rapidjson::Document doc;
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
    doc.SetObject();
    rapidjson::Value accelerationObject;
    accelerationObject.SetObject();
    accelerationObject.AddMember("x", rapidjson::Value().SetDouble(1), allocator);
    accelerationObject.AddMember("y", rapidjson::Value().SetDouble(2), allocator);
    accelerationObject.AddMember("z", rapidjson::Value().SetDouble(3), allocator);
    doc.AddMember("acceleration", accelerationObject, allocator);
    handleAPIPostPhysicsRequest(doc);

    rapidjson::Document docResult;
	getPhysicsDocument(docResult);
    unitTest.assertTrue(docResult["acceleration"]["x"].GetDouble() == 1, "acceleration.x should be 1");
    unitTest.assertTrue(docResult["acceleration"]["y"].GetDouble() == 2, "acceleration.y should be 2");
    unitTest.assertTrue(docResult["acceleration"]["z"].GetDouble() == 3, "acceleration.z should be 3");

    // minimize side effects of running this test.
    handleAPIPostPhysicsRequest(originalStateDoc);
}

void testPropellerSpeedWriteAndRead(UnitTest& unitTest)
{
    const string propellerName = "propeller-293()85$-7"; // some name unlikely to ever be configured.
    // add a device to the UAVPhysicalState
    UAVPhysicalState* uavState = UAVPhysicalState::getInstance();
    PropellerMotor pmDevice;
    pmDevice.name = propellerName;
    PropellerMotorPhysicalState pm;
    pm.motor = &pmDevice;
    pm.bladeAngleDegrees = 1;
    pm.bladeAccelerationDegreesPerSecondPerSecond = 0;
    pm.bladeRotationSpeedDegreesPerSecond = 5;

    uavState->propellerMotors.push_back(pm);

    rapidjson::Document doc;
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
    doc.SetObject();
    rapidjson::Value devicesArray;
    devicesArray.SetArray();
    rapidjson::Value propellerObject;
    propellerObject.SetObject();
    rapidjson::Value deviceObject;
    deviceObject.SetObject();
    deviceObject.AddMember("name", rapidjson::Value().SetString(pmDevice.name.c_str(), pmDevice.name.length(), allocator), allocator);
    propellerObject.AddMember("device", deviceObject, allocator);
    propellerObject.AddMember("bladeRotationSpeedDegreesPerSecond", rapidjson::Value().SetDouble(2), allocator);

    devicesArray.PushBack(propellerObject, allocator);
    doc.AddMember("devices", devicesArray, allocator);

    handleAPIPostPhysicsRequest(doc);

    rapidjson::Document newStateDoc;
    getPhysicsDocument(newStateDoc);

    rapidjson::Value& devices = newStateDoc["devices"];
    unitTest.assertTrue(devices.IsArray(), "devices should be an array.");
    // loop through devices.
    for (rapidjson::Value::ValueIterator itr = devices.Begin(); itr != devices.End(); ++itr)
    {
        rapidjson::Value & device = (*itr)["device"];
        if (device["name"].GetString() == propellerName)
        {
            unitTest.assertTrue((*itr)["bladeAngleDegrees"].GetDouble()==1, "bladeAngleDegrees should remain at 1.");
            unitTest.assertTrue((*itr)["bladeRotationSpeedDegreesPerSecond"].GetDouble()==2, "bladeRotationSpeedDegreesPerSecond should be 2.");
            break;
        }
    }

    // remove the temporary propeller so there is no side effects of this function.
    uavState->propellerMotors.pop_back();
}

void testPhysicsHTTPPostTime(UnitTest& unitTest)
{
    rapidjson::Document doc;
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
    doc.SetObject();
	doc.AddMember("seconds", rapidjson::Value().SetDouble(0.1), allocator);
	handleAPIPostPhysicsTimeChangeRequest(doc);
}

PhysicsAPITest::PhysicsAPITest(): UnitTest("PhysicsAPITest")
{
    testFunctions.push_back(make_pair("physicsHTTPGET", testPhysicsHTTPGet));
    testFunctions.push_back(make_pair("physics write and read acceleration", testAccelerationWriteAndRead));
    testFunctions.push_back(make_pair("physics write and read propeller speed", testPropellerSpeedWriteAndRead));
    testFunctions.push_back(make_pair("time Change API", testPhysicsHTTPPostTime));
}
