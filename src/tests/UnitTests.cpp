#include "UnitTests.hpp"
#include "TriangleFiltersTest.hpp"
#include <vector>
#include <iostream>
using namespace std;

void runAllUnitTests()
{
    cerr << "runAllUnitTests()" << endl;
	vector<UnitTest> unitTests({
		TriangleFiltersTest()
	});
    for (UnitTest & test: unitTests)
    {
        test.printResults();
    }
}
