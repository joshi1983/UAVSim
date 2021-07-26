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
	state.setValue("blade-1-angle", 2.0);
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
    sanitized = state.sanitizeName("shape1colour");
    unitTest.assertTrue(sanitized == "shape-1-colour", "Sanitized shape1colour");
    sanitized = state.sanitizeName("shape1visible");
    unitTest.assertTrue(sanitized == "shape-1-visible", "Sanitized shape1visible");
}

void testGetTypeFor(UnitTest& unitTest)
{
    AnimationStateKeyType result = AnimationState::getTypeFor("shape-1-colour");
    unitTest.assertTrue(result == AnimationStateKeyType::tColour, "checked type for shape-1-colour");
    result = AnimationState::getTypeFor("shape-1-visible");
    unitTest.assertTrue(result == AnimationStateKeyType::tBool, "checked type for shape-1-visible");
    result = AnimationState::getTypeFor("blade-1-angle");
    unitTest.assertTrue(result == AnimationStateKeyType::tDouble, "checked type for blade-1-angle");
}

AnimationStateTest::AnimationStateTest(): UnitTest("AnimationStateTest")
{
    testFunctions.push_back(make_pair("set blade-1-angle", testSetBlade1Angle));
    testFunctions.push_back(make_pair("sanitizeName", testSanitizeName));
    testFunctions.push_back(make_pair("getTypeFor", testGetTypeFor));
}
