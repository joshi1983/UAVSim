#include "UnitTests.hpp"
#include "TriangleFiltersTest.hpp"
#include "TriangleFilterFactoryTest.hpp"
#include "Vector3DTest.hpp"
#include <vector>
#include <iostream>
using namespace std;

void runAllUnitTests()
{
    cerr << "runAllUnitTests()" << endl;
	vector<UnitTest> unitTests({
		TriangleFiltersTest(),
        TriangleFilterFactoryTest(),
		Vector3DTest()
	});
    for (UnitTest & test: unitTests)
    {
        test.printResults();
    }
}
