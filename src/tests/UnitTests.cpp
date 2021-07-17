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
		PhysicsAPITest()
	});
    for (UnitTest & test: unitTests)
    {
        test.printResults();
    }
}
