#include "TriangleSetAnimationPropertiesTest.hpp"
#include "../../models/animation/TriangleSetAnimationProperties.hpp"
using namespace std;

void testConstructors(UnitTest& unitTest)
{
	TriangleSetAnimationProperties p1; // no-argument constructor.
	unitTest.assertTrue(p1.isVisible, "A shape should be visible by default.");
	unitTest.assertTrue(p1.colour.str() == "#ffffff", "A shape's colour should be white by default.");
	p1.isVisible = false;
	p1.colour = Colour(1, 0, 0);
	unitTest.assertTrue(p1.colour.str() == "#ff0000", "Colour for p1 expected to be #ff0000.");
	TriangleSetAnimationProperties p2 = p1; // call copy constructor.
	unitTest.assertTrue(p2.colour.str() == "#ff0000", "Colour for p2 expected to be #ff0000.");
	unitTest.assertTrue(p2.isVisible == false, "isVisible for p2 expected to be false.");
}

void testBlend(UnitTest& unitTest)
{
    TriangleSetAnimationProperties p1;
    p1.colour = Colour(0, 0.5, 1);
    p1.isVisible = true;
    TriangleSetAnimationProperties p2;
    p2.colour = Colour(1, 0, 0);
    p2.isVisible = false;
    TriangleSetAnimationProperties blended = TriangleSetAnimationProperties::blend(p1, p2, 0.5);
    unitTest.assertTrue(blended.isVisible == false, "Since 0.5 is not less than 0.5, p2.isVisible should be used.");
    unitTest.assertTrue(blended.colour.str() == "#804080", "Expected blend value to be #804080");
}

TriangleSetAnimationPropertiesTest::TriangleSetAnimationPropertiesTest(): UnitTest("TriangleSetAnimationProperties")
{
	testFunctions.push_back(make_pair("constructors", testConstructors));
	testFunctions.push_back(make_pair("blend", testBlend));
}
