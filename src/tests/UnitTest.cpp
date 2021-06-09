#include "UnitTest.hpp"
#include <iostream>
using namespace std;

UnitTest::UnitTest(const string &name): name(name)
{

}

void UnitTest::printResults()
{
    messages.clear();
	for (pair<string, UnitTestFunc> m: testFunctions)
	{
	    testFunctionName = m.first;
		 (*m.second)(*this);
	}
	if (messages.size() == 0)
        cout << "All " << name << " tests passed." << endl;
    else {
        cout << messages.size() << " failure messages in test " << name << ".  They are:" << endl;
        for (string message: messages)
        {
            cout << message << endl;
        }
    }
}

void UnitTest::assertTrue(bool result, const std::string & message)
{
	if (!result)
		messages.push_back(testFunctionName + ": " + message);
}
