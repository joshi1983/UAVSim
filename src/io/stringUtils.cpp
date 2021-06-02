#include "stringUtils.hpp"
#include <algorithm>
using namespace std;

string trim(const string & s)
{
    int starting;
    int ending;
    for (starting = 0; isspace(s[starting]) && s[starting] != '\0'; starting++); // find first non-whitespace.
    for (ending = s.length() - 1; starting < ending && isspace(s[ending]); ending--);

    return s.substr(starting, ending - starting + 1);
}

string toLower(const string &s)
{
	string result = s;
	std::for_each(result.begin(), result.end(), [](char & c){
		c = ::tolower(c);
	});
	return result;
}

void convertToWCharString(const char * from, wchar_t * result)
{
    unsigned int i;
    for (i = 0; from[i] != '\0'; i++)
    {
        result[i] = from[i];
    }
    result[i] = '\0';
}
