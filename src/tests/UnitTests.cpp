#include "UnitTests.hpp"
#include "TriangleFiltersTest.hpp"
#include "TriangleFilterFactoryTest.hpp"
#include "Vector3DTest.hpp"
#include "AnimationStateTest.hpp"
#include "physics/PropellerMotorPhysicalStateTest.hpp"
#include "physics/UAVPhysicalStateTest.hpp"
#include "physics/JSONPhysicalStateLoaderTest.hpp"
#include "devices/PropellerMotorTest.hpp"
#include "io/PhysicsAPITest.hpp"
#include "io/JsonUtilsTest.hpp"
#include <vector>
#include <iostream>
using namespace std;

void runAllUnitTests()
{
    cerr << "runAllUnitTests()" << endl;
	vector<UnitTest> unitTests({
		TriangleFiltersTest(),
		TriangleFilterFactoryTest(),
		Vector3DTest(),
		AnimationStateTest(),
		PropellerMotorTest(),
		PropellerMotorPhysicalStateTest(),
		UAVPhysicalStateTest(),
		JSONPhysicalStateLoaderTest(),
		PhysicsAPITest(),
		JsonUtilsTest()
	});
    for (UnitTest & test: unitTests)
    {
        test.printResults();
    }
}
