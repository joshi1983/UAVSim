#include "stringUtils.hpp"
#include <algorithm>
#include <cctype>
#include <sstream>
using namespace std;

/*
Copied from: https://java2blog.com/split-string-space-cpp/
*/
void tokenize(string const &str, const char delim, vector<string> &out)
{
    // construct a stream from the string
    stringstream ss(str);

    string s;
    while (getline(ss, s, delim)) {
        out.push_back(s);
    }
}

/*
Replaces all whitespaces with ' ' and
consecutive whitespaces are reduced to a single ' '.
*/
string simplifyWhitespaces(const string &s)
{
	char * resultChars = new char[s.length() + 1];
	char * resultPtr = resultChars;
	for (unsigned int i = 0; i < s.length(); i++)
	{
		char c = s[i];
		if (isspace(c) && (i == 0 || !isspace(s[i - 1])))
		{
			*(resultPtr++) = ' ';
		}
		else if (!isspace(c))
		{
			*(resultPtr++) = c;
		}
	}
	*resultPtr = '\0'; // mark end of string
	string result(resultChars);
	delete [] resultChars; // prevent memory leak.
	return result;
}

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

void convertToTCharString(const char * from, TCHAR * result)
{
    unsigned int i;
    for (i = 0; from[i] != '\0'; i++)
    {
        result[i] = from[i];
    }
    result[i] = '\0';
}

/*
This was copied from: https://thispointer.com/find-and-replace-all-occurrences-of-a-sub-string-in-c/
*/
void findAndReplaceAll(std::string & data, std::string toSearch, std::string replaceStr)
{
    // Get the first occurrence
    size_t pos = data.find(toSearch);
    // Repeat till end is reached
    while( pos != std::string::npos)
    {
        // Replace this occurrence of Sub String
        data.replace(pos, toSearch.size(), replaceStr);
        // Get the next occurrence from the current position
        pos =data.find(toSearch, pos + replaceStr.size());
    }
}
