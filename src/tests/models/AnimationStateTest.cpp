#include "AnimationStateTest.hpp"
#include "../../models/animation/AnimationState.hpp"
#include <cmath>
#include <iostream>
using namespace std;

void testSetBlade1Angle(UnitTest& unitTest)
{
	AnimationState state;
	state.blade1Angle = 3;
    unitTest.assertTrue(state.blade1Angle == 3, "blade-1-angle to 3");
	state.setValue("blade-1-angle", 2);
    unitTest.assertTrue(state.blade1Angle == 2, "blade-1-angle to 2");
}

void testSanitizeName(UnitTest& unitTest)
{
	AnimationState state;
    string sanitized = state.sanitizeName("blade-1-angle");
    unitTest.assertTrue(sanitized == "blade-1-angle", "Sanitized blade-1-angle");
    sanitized = state.sanitizeName("blade1angle");
    unitTest.assertTrue(sanitized == "blade-1-angle", "Sanitized blade1angle");
    sanitized = state.sanitizeName("Blade1Angle");
    unitTest.assertTrue(sanitized == "blade-1-angle", "Sanitized Blade1Angle");
}

AnimationStateTest::AnimationStateTest(): UnitTest("AnimationStateTest")
{
    testFunctions.push_back(make_pair("set blade-1-angle", testSetBlade1Angle));
    testFunctions.push_back(make_pair("sanitizeName", testSanitizeName));
}
