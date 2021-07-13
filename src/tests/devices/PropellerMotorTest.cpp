#include "PropellerMotorTest.hpp"
#include "../../devices/PropellerMotor.hpp"
using namespace std;

void testGetThrustNewtonsFromRotationSpeedDegreesPerSecond(UnitTest& unitTest)
{
	PropellerMotor device;
	device.newtonsOfThrustAtOneRotationPerSecond = 1;
	Vector3D v = device.getThrustNewtonsFromRotationSpeedDegreesPerSecond(1);
    unitTest.assertTrue(v.y == 1, "1 newton of thrust expected.");
	v = device.getThrustNewtonsFromRotationSpeedDegreesPerSecond(2);
    unitTest.assertTrue(v.y == 4, "4 newtons of thrust expected.");
}

PropellerMotorTest::PropellerMotorTest(): UnitTest("PropellerMotorTest")
{
    testFunctions.push_back(make_pair("getThrustNewtonsFromRotationSpeedDegreesPerSecond", testGetThrustNewtonsFromRotationSpeedDegreesPerSecond));
}
