#include "ColourTest.hpp"
#include "../../models/Colour.hpp"
#include <cmath>
#include <iostream>
using namespace std;

void testStr(UnitTest& unitTest)
{
	Colour c(0,0,0);
	string htmlColour = c.str();
	unitTest.assertTrue(htmlColour == "#000000", "Colour 0,0,0 should be formatted as #000000.");
	c.r = 0.5;
	unitTest.assertTrue(c.str() == "#800000", "Colour 0.5,0,0 should be formatted as #800000.");
	c.r = 1;
	unitTest.assertTrue(c.str() == "#ff0000", "Colour 1,0,0 should be formatted as #ff0000.");
	c.g = 1;
	unitTest.assertTrue(c.str() == "#ffff00", "Colour 1,1,0 should be formatted as #ffff00.");
	c.b = 1;
	unitTest.assertTrue(c.str() == "#ffffff", "Colour 1,1,1 should be formatted as #ffffff.");
}

void testLoadFrom(UnitTest& unitTest)
{
    const double precisionThreshold = 0.01;
	Colour c(1,1,1);
	c.loadFrom("#000000");
	unitTest.assertTrue(c.r == 0, "r expected to be 0.");
	unitTest.assertTrue(c.g == 0, "g expected to be 0.");
	unitTest.assertTrue(c.b == 0, "b expected to be 0.");
	c.loadFrom("#ff0000");
	unitTest.assertTrue(abs(c.r - 1) < precisionThreshold, "#ff0000: r expected to be 1.");
	unitTest.assertTrue(c.g == 0, "#ff0000: g expected to be 0.");
	unitTest.assertTrue(c.b == 0, "#ff0000: b expected to be 0.");
	c.loadFrom("#ff8000");
	unitTest.assertTrue(abs(c.r - 1) < precisionThreshold, "#ff8000: r expected to be 1.");
	unitTest.assertTrue(abs(c.g - 0.5) < precisionThreshold, "#ff8000: g expected to be 0.5.");
	unitTest.assertTrue(c.b == 0, "#ff8000: b expected to be 0.");
	c.loadFrom("#ff80ff");
	unitTest.assertTrue(abs(c.r - 1) < precisionThreshold, "#ff80ff: r expected to be 1.");
	unitTest.assertTrue(abs(c.g - 0.5) < precisionThreshold, "#ff80ff: g expected to be 0.5.");
	unitTest.assertTrue(abs(c.b - 1) < precisionThreshold, "#ff80ff: b expected to be 1.");

	// 1 digit per r,g,b component
	c.loadFrom("#fff");
	unitTest.assertTrue(abs(c.r - 1) < precisionThreshold, "#fff: r expected to be 1.");
	unitTest.assertTrue(abs(c.g - 1) < precisionThreshold, "#fff: g expected to be 1.");
	unitTest.assertTrue(abs(c.b - 1) < precisionThreshold, "#fff: b expected to be 1.");
}

void testCopyConstructor(UnitTest& unitTest)
{
    Colour c(1, 0, 0.5);
    Colour c2 = c;
	unitTest.assertTrue(c2.r == 1, "c2.r expected to be 1.");
	unitTest.assertTrue(c2.g == 0, "c2.g expected to be 0.");
	unitTest.assertTrue(c2.b == 0.5, "c2.b expected to be 0.5.");
}

ColourTest::ColourTest(): UnitTest("ColourTest")
{
	testFunctions.push_back(make_pair("str", testStr));
	testFunctions.push_back(make_pair("loadFrom", testLoadFrom));
	testFunctions.push_back(make_pair("copyConstructor", testCopyConstructor));
}

