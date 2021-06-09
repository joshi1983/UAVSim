#ifndef UNIT_TEST_HEADER_INCLUDED
#define UNIT_TEST_HEADER_INCLUDED
#include <vector>
#include <string>

class UnitTest;

typedef void (*UnitTestFunc)(UnitTest&);

class UnitTest {
	private:
	    std::string name;
	    std::string testFunctionName;
		std::vector<std::string> messages;
    protected:
		std::vector<std::pair<std::string, UnitTestFunc>> testFunctions;
		UnitTest(const std::string &name);
	public:
		void printResults();
		void assertTrue(bool result, const std::string & message);
};

#endif
