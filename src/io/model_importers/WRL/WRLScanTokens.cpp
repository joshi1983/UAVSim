#include "WRLScanTokens.hpp"
#include <iostream>
#include <regex>
#include <cctype>
using namespace std;


// 	Implementation of: [A-Z]+[_|A-Z]*
int checkSFEnumMatch(const char *s)
{
    int result = 0;
    if (s[0] < 'A' || s[0] > 'Z')
        return -1; // must start with a capital letter.
    while (s[result] >= 'A' && s[result] <= 'Z')
        result++;
    while (s[result] == '_' || (s[result] >= 'A' && s[result] <= 'Z'))
        result++;
    return result;
}

int checkStringMatch(const char *s)
{
    if (s[0] != '"')
        return -1;
    int result = 1;
    while (s[result] != '"' && s[result] != '\0')
        result++;
    if (s[result] == '\0')
        return -1; // no matching quote to close the string so no match.
    return result;
}

// This is basically a c++ implementation of a regular expression:
// [\-]?[0-9]+(\.[0-9]+)([e|E][\-\+]?[0-9]+)
int checkFloatMatch(const char * s)
{
    int result = 0;
    if (s[result] == '-')
        result++;
    if (s[result] < '0' || s[result] > '9')
        return -1; // digit must either start or follow the negative sign
    while (s[result] >= '0' && s[result] <= '9')
        result++;
    if (s[result] == '.')
    {
        result++;
        if (s[result] < '0' || s[result] > '9')
            return -1; // at least 1 digit must follow the .
        while (s[result] >= '0' && s[result] <= '9')
            result++;
    }
    int resultBeforeE = result;
    if (s[result] == 'e' || s[result] == 'E')
    {
        result++;
        if (s[result] == '-' || s[result] == '+')
            result++;
        if (s[result] < '0' || s[result] > '9')
            return resultBeforeE; // at least 1 digit must follow the e or +/- symbols
        while (s[result] >= '0' && s[result] <= '9')
            result++;
    }
    return result;
}

// This is basically a c++ implementation of a regular expression:
// float( float)*
// where float is the same regular expression as for checkFloatMatch.
//
// I wish I could have left this as a regular expression but I wasn't able
// to resolve a crashing error that kept happening with matches several 1000 characters
// long using sregex_iterator.
int checkFloatArrayMatch(const char * s)
{
    int result = checkFloatMatch(s);
    if (result < 0)
        return -1; // an array must match at least 1 float.
    while (s[result] == ' ')
    {
        int floatResult = checkFloatMatch(s + result + 1);
        if (floatResult == -1)
            return result;
        else
            result += floatResult + 1;
    }
    return result;
}

typedef int(*matchFunction) (const char *) ;

const int numAttributeValueMatchers = 3;
const matchFunction tokenMatchers[numAttributeValueMatchers] = {
    checkStringMatch,
    checkSFEnumMatch,
    checkFloatArrayMatch
};

string trim(const string & s)
{
    int starting;
    int ending;
    for (starting = 0; isspace(s[starting]) && s[starting] != '\0'; starting++); // find first non-whitespace.
    for (ending = s.length() - 1; starting < ending && isspace(s[ending]); ending--);

    return s.substr(starting, ending - starting + 1);
}

bool isAttributeValueStartCharacter(char c)
{
    if (c >= 'A' && c <= 'Z')
        return true;
    if (c >= '0' && c <= '9')
        return true;
    if (c == '-' || c == '"')
        return true;
    return false;
}

void getAttributeValueMatches(const string & content, map<int, string> & result)
{
    sregex_iterator ending;
    for (unsigned int i = 1; i < content.length() - 1; i++)
    {
        if (isspace(content[i - 1]) && isAttributeValueStartCharacter(content[i]))
        {
            bool matchFound = false;
            for (unsigned int j = 0; j < numAttributeValueMatchers; j++)
            {
                int len = tokenMatchers[j](content.c_str() + i);
                if (len < 0 || content.length() <= (unsigned int)(len + i))
                    continue; // end of string or no match so just continue.
                else if (content[len + i] != ' ' && content[len + i] != ']')
                    continue;
                if (len > 0 && (!matchFound || (unsigned int)len > result[i].length())) {
                    result[i] = content.substr(i, len);
                    matchFound = true;
                }
            }
            if (matchFound)
                i += result[i].length() - 1;
        }
    }
}

void getScanTokensFromVRML(const string & content, vector<string> &tokens)
{
    const string brackets("[]{}");
    map<int, string> attributeValueMatches;
    getAttributeValueMatches(content, attributeValueMatches);
    string token;
	for (unsigned int i = 0; i < content.length(); i++) {
		char c = content[i];
		if (brackets.find(c) != string::npos)
        {
			token = trim(token);
			if (token.length() != 0)
            {
				tokens.push_back(token);
				token = "";
			}
			tokens.push_back(string(1, c));
		}
		else {
            map<int, string>::const_iterator it = attributeValueMatches.find(i);
            if (it != attributeValueMatches.end()) {
                token = trim(token);
                if (token.length() != 0) {
                    tokens.push_back(token);
                    token = "";
                }
                token = attributeValueMatches[i];
                tokens.push_back(token);
                i += token.length() - 1;
                token = "";
            }
            else
                token += c;
		}
	}
	token = trim(token);
	if (token != "")
		tokens.push_back(token);
}

bool isAttributeToken(const string & token)
{
    if (token == "[")
        return true;
    if ((unsigned int)checkFloatArrayMatch(token.c_str()) == token.length())
        return true;

    for (int i = 0; i < numAttributeValueMatchers; i++)
        if ((unsigned int)tokenMatchers[i](token.c_str()) == token.length())
            return true;

    return false;
}
