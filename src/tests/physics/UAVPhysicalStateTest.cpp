#include "UAVPhysicalStateTest.hpp"
#include "../../physics/UAVPhysicalState.hpp"
using namespace std;

void testCopyInto(UnitTest& unitTest)
{
	UAVPhysicalState* state = UAVPhysicalState::getInstance();
	state->displacement = Vector3D(1, 2, 3);
	state->pitchDegrees = 4;
	state->rollDegrees = 5;
	state->yawDegrees = 6;
	AnimationState animationState;
	state->copyInto(animationState);
	unitTest.assertTrue(animationState.x == 1, "animationState x should be 1");
	unitTest.assertTrue(animationState.y == 2, "animationState y should be 2");
	unitTest.assertTrue(animationState.z == 3, "animationState z should be 3");
	unitTest.assertTrue(animationState.pitch == 4, "animationState pitch should be 4");
	unitTest.assertTrue(animationState.roll == 5, "animationState roll should be 5");
	unitTest.assertTrue(animationState.yaw == 6, "animationState yaw should be 6");
}

UAVPhysicalStateTest::UAVPhysicalStateTest(): UnitTest("UAVPhysicalStateTest")
{
    testFunctions.push_back(make_pair("copyInto", testCopyInto));
}
