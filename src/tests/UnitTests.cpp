#include "UnitTests.hpp"
#include "models/TriangleFiltersTest.hpp"
#include "models/TriangleFilterFactoryTest.hpp"
#include "models/Vector3DTest.hpp"
#include "models/ColourTest.hpp"
#include "models/AnimationStateTest.hpp"
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
		ColourTest(),
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
