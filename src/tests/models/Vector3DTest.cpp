#include "Vector3DTest.hpp"
#include "../../models/Vector3D.hpp"
#include <cmath>
using namespace std;

void testNormalize(UnitTest& unitTest)
{
	Vector3D v(0,0,0);
	v.normalize();
	unitTest.assertTrue(v.magnitude() == 1, "magnitude should be 1.");
	v.x = 2;
	v.y = 0;
	v.z = 0;
	v.normalize();
	unitTest.assertTrue(abs(v.magnitude() - 1) < 0.001, "magnitude should be 1.");
}

void testMagnitude(UnitTest& unitTest)
{
	Vector3D v(0,0,0);
	unitTest.assertTrue(v.magnitude() == 0, "magnitude should be 0.");
	v.x = 1;
	unitTest.assertTrue(v.magnitude() == 1, "magnitude should be 1.");
	v.y = 1;
	unitTest.assertTrue(abs(v.magnitude() - 1.4142) < 0.001, "magnitude should be roughly 1.4142(square root of 2).");
	v.z = 1;
	unitTest.assertTrue(abs(v.magnitude() - 1.732) < 0.001, "magnitude should be roughly 1.732(square root of 3).");
}

Vector3DTest::Vector3DTest(): UnitTest("Vector3DTest")
{
	testFunctions.push_back(make_pair("Magnitude", testMagnitude));
	testFunctions.push_back(make_pair("Normalize", testNormalize));
}

