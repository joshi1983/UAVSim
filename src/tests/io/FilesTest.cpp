#include "FilesTest.hpp"
#include "../../io/Files.hpp"
#include <iostream>
using namespace std;

void testGetAbsolutePathForFilename(UnitTest& unitTest)
{
	string result = getAbsolutePathForFilename("c:\\bin\\uavsim.exe", "data/settings.json");
	unitTest.assertTrue(result == "c:\\data/settings.json", "bin checked.  Expected to be c:\\data/settings.json");
	result = getAbsolutePathForFilename("c:\\src\\bin\\Debug\\uavsim.exe", "data/settings.json");
	unitTest.assertTrue(result == "c:\\data/settings.json", "Debug checked. Expected to be c:\\data/settings.json");
	result = getAbsolutePathForFilename("c:\\src\\bin\\Release\\uavsim.exe", "data/settings.json");
	unitTest.assertTrue(result == "c:\\data/settings.json", "Release checked. Expected to be c:\\data/settings.json");
}

FilesTest::FilesTest(): UnitTest("FilesTest")
{
    testFunctions.push_back(make_pair("getAbsolutePathForFilename", testGetAbsolutePathForFilename));
}
