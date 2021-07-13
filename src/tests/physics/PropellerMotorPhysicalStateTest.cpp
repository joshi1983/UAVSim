#include "PropellerMotorPhysicalStateTest.hpp"
#include "../../devices/PropellerMotor.hpp"
#include "../../physics/PropellerMotorPhysicalState.hpp"
#include <iostream>
using namespace std;

void testGetThrustNewtons(UnitTest& unitTest)
{
	PropellerMotor device;
	device.newtonsOfThrustAtOneRotationPerSecond = 1;
	PropellerMotorPhysicalState propellerPhysicalState;
	propellerPhysicalState.motor = &device;
    propellerPhysicalState.bladeRotationSpeedDegreesPerSecond = 360;
	Vector3D v = propellerPhysicalState.getThrustNewtons();
    unitTest.assertTrue(v.y == 1, "1 newton of thrust expected.");
    propellerPhysicalState.bladeRotationSpeedDegreesPerSecond = 720;
	v = propellerPhysicalState.getThrustNewtons();
    unitTest.assertTrue(v.y == 4, "4 newtons of thrust expected.");
}

PropellerMotorPhysicalStateTest::PropellerMotorPhysicalStateTest(): UnitTest("PropellerMotorPhysicalStateTest")
{
    testFunctions.push_back(make_pair("getThrustNewtons", testGetThrustNewtons));
}

