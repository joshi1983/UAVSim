#include "JSONPhysicalStateLoaderTest.hpp"
#include "../../physics/jsonPhysicalStateLoader.hpp"
using namespace std;

void testLoadPhysicalStateFromJSONObject(UnitTest& unitTest)
{
	rapidjson::Document doc;
	rapidjson::Document::AllocatorType&  allocator = doc.GetAllocator();
	doc.SetObject();
	rapidjson::Value val;
	val.SetObject();
	val.AddMember("bladeAccelerationDegreesPerSecondPerSecond", rapidjson::Value().SetDouble(1), allocator);
	val.AddMember("bladeRotationSpeedDegreesPerSecond", rapidjson::Value().SetDouble(2), allocator);
	val.AddMember("bladeAngleDegrees", rapidjson::Value().SetDouble(3), allocator);
	PropellerMotorPhysicalState motor;
	loadPhysicalStateFromJSONObject(val, motor);
	unitTest.assertTrue(motor.bladeAccelerationDegreesPerSecondPerSecond == 1, "bladeAccelerationDegreesPerSecondPerSecond expected to be 1");
	unitTest.assertTrue(motor.bladeRotationSpeedDegreesPerSecond == 2, "bladeRotationSpeedDegreesPerSecond expected to be 2");
	unitTest.assertTrue(motor.bladeAngleDegrees == 3, "bladeAngleDegrees expected to be 3");
}

JSONPhysicalStateLoaderTest::JSONPhysicalStateLoaderTest(): UnitTest("JSONPhysicalStateLoaderTest")
{
    testFunctions.push_back(make_pair("loadPhysicalStateFromJSONObject", testLoadPhysicalStateFromJSONObject));
}
