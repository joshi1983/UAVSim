#include "WRLUtils.hpp"
#include <sstream>
#include <iostream>
#include "WRLScanTokens.hpp"
using namespace std;

TiXmlElement* vrmlToX3DElement(const vector<string> & tokens, unsigned int & startIndex);

void splitByWhitespace(const string& s, vector<string>& result)
{
    int lastStart = -1;
    for (unsigned int i = 0; i < s.length(); i++)
    {
        if (isspace(s[i]))
        {
            if (lastStart != -1)
            {
                result.push_back(s.substr(lastStart, i - lastStart));
                lastStart = -1;
            }
        }
        else if (lastStart == -1)
            lastStart = i;
    }
   if (lastStart != -1)
        result.push_back(s.substr(lastStart));
}

void vrmlToX3DAttribute(const vector<string> & tokens, unsigned int& startIndex, string &name, string &value) {
	name = tokens[startIndex];
	if (tokens[startIndex + 1] == string("["))
    {
		if (tokens[startIndex + 2] == string("]"))
		{
			value = "";
			startIndex += 3;
		}
		else
		{
			value = tokens[startIndex + 2];
			startIndex += 4;
		}
	}
	else
	{
		value = tokens[startIndex + 1];
		startIndex += 2;
	}
}

string getTagNameFor(const string &s)
{
    vector<string> parts;
    splitByWhitespace(s, parts);
	if (parts.size() == 1)
		return parts[0];
    // Return the first part starting with a capital.
    for (auto part = parts.begin(); part != parts.end(); part++)
    {
        if (isupper((*part)[0]))
            return *part;
    }
    if (parts.size() > 1)
        return parts[parts.size() - 1];
	return "";
}

bool isValidTagName(const string &s)
{
    return s[0] >= 'A' && s[0] <= 'Z';
}

string removeComments(const char * content)
{
	stringstream result;
	bool in_comment = false;
	for (int i = 0; content[i] != '\0'; i++)
	{
		if (content[i] == '#')
			in_comment = true;
		else if (content[i] == '\n')
			in_comment = false;
		if (!in_comment)
			result << content[i];
	}

	return result.str();
}

// removes duplicated whitespaces and replaces any
// Also, replaces comma with space when it isn't in a string literal.
string simplifyWhitespaces(const char * content)
{
	stringstream result;
	bool in_string = false;
	for (int i = 0; content[i] != '\0'; i++)
	{
		if (content[i] == '"')
        {
			in_string = !in_string;
            result << '"';
        }
		else if (in_string)
            result << content[i];
        else if (isspace(content[i]) || content[i] == ',')
        {
            if (i == 0 || (!isspace(content[i - 1]) && content[i - 1] != ','))
                result << ' ';
        }
        else
            result << content[i];
	}

	return result.str();
}

void loadChildrenFromTokens(TiXmlElement &parentElement, char closingBracket, const vector<string>& tokens, unsigned int &startIndex) {
    const string closingBracketStr(1, closingBracket);
    const string brackets("[]{}");
	while (startIndex < tokens.size() && tokens[startIndex] != closingBracketStr) {
		if (brackets.find(tokens[startIndex]) != string::npos) {
			cerr << "Expected to close children section with " << closingBracket <<
                " but found " << tokens[startIndex] << " at token index " << startIndex << endl;
			return;
		}
		else if (isAttributeToken(tokens[startIndex + 1])) {
			string name, value;
			vrmlToX3DAttribute(tokens, startIndex, name, value);
			if (name == "children" && tokens[startIndex + 1] == string("[")) {
				loadChildrenFromTokens(parentElement, ']', tokens, startIndex);
				startIndex ++;
			}
			else {
				parentElement.SetAttribute(name.c_str(), value.c_str());
			}
		}
		else {
		    //cout << "About to create element" << endl;
			TiXmlElement* childElement = vrmlToX3DElement(tokens, startIndex);
			parentElement.LinkEndChild(childElement);
		}
	}
}

TiXmlElement* vrmlToX3DElement(const vector<string> & tokens, unsigned int & startIndex)
{
	const string tagName = getTagNameFor(tokens[startIndex]);
	if (!isValidTagName(tagName))
    {
        cerr << "Invalid tag name: " << tagName << " at token index " << startIndex << endl;
        throw InvalidVRMLElementNameException(string("Invalid tagName: ") + tagName);
    }
	if (tokens[startIndex + 1] != "{")
    {
		cerr << "Expected { but " << tokens[startIndex + 1] << " found at token " << (startIndex + 1)
            << ".  Trying to create element with tag name " << tagName << endl;
        cerr << "tokens.size() is " << tokens.size() << endl;
        unsigned int i = 0;
        if (startIndex > 5)
            i = startIndex - 5;
        for (; i < tokens.size() && i < startIndex + 10; i++)
        {
            cout << i <<  ": '";
            if (tokens[i].length() > 30)
                cout << tokens[i].substr(0, 30) << "..." ;
            else
                cout << tokens[i];
            cout << "'" << endl;
        }

        return NULL;
    }
	TiXmlElement *resultElement = new TiXmlElement(tagName.c_str());
	startIndex += 2;
	loadChildrenFromTokens(*resultElement, '}', tokens, startIndex);
    startIndex++;

    return resultElement;
}

TiXmlDocument * vrmlToX3DDocument(const string & _content)
{
	string content = "Scene { " + simplifyWhitespaces(removeComments(_content.c_str()).c_str()) + " }";
	vector<string> tokens;
	getScanTokensFromVRML(content, tokens);

	TiXmlDocument * result = new TiXmlDocument("X3D");
	unsigned int startIndex = 0;
    TiXmlElement * scene = vrmlToX3DElement(tokens, startIndex);
    result->LinkEndChild(scene);
	return result;
}
