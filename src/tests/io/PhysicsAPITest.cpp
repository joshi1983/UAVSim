#include "PhysicsAPITest.hpp"
#include "../../io/networking/http_server/physics_api_handlers.hpp"
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
}

void testAccelerationWriteAndRead(UnitTest& unitTest)
{
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
}

PhysicsAPITest::PhysicsAPITest(): UnitTest("PhysicsAPITest")
{
    testFunctions.push_back(make_pair("physicsHTTPGET", testPhysicsHTTPGet));
    testFunctions.push_back(make_pair("physics write and read acceleration", testAccelerationWriteAndRead));
}
