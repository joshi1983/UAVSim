#include "CSVParser.hpp"
#include <fstream>
#include <sstream>
#include "../stringUtils.hpp" // defines trim function
using namespace std;

CSVParser::CSVParser(const char delimiter, const bool trimValues,
    const bool delimitersInQuotes, const bool processEscapeCharacters):
    delimiter(delimiter), trimValues(trimValues), delimitersInQuotes(delimitersInQuotes),
    processEscapeCharacters(processEscapeCharacters)
{
}

std::string CSVParser::sanitizeValue(const std::string & value) const
{
    if (this->trimValues)
        return trim(value);
    else
        return value;
}

vector<vector<string>> CSVParser::parse(istream & in)
{
	vector<vector<string>> result;
    string line;
    ostringstream curValue;
    while (getline(in, line))
    {
        // Skip blank lines at the beginning of the file, if there are any.
        if (trim(line) == "" && result.size() == 0)
            continue;
        vector<string> rowValues;
        char quoteChar = '\0';
        for (unsigned int i = 0; i < line.length(); i++)
        {
            char c = line[i];
            if (delimitersInQuotes && (c == '"' || c == '\''))
            {
                if (quoteChar == '\0')
                    quoteChar = c;
                else
                    quoteChar = '\0'; // indicate not in quoted mode.
            }
            else if (processEscapeCharacters && c == '\\' && i < line.length() - 1)
            { // process escape character.
                curValue << line[++i];
            }
            else if (c == delimiter && quoteChar == '\0')
            {
                rowValues.push_back(sanitizeValue(curValue.str()));
                curValue.str("");
            }
            else
            {
                curValue << c;
            }
        }
        if (curValue.str() != "")
        {
            rowValues.push_back(sanitizeValue(curValue.str()));
            curValue.str("");
        }
        result.push_back(rowValues);
    }

	return result;
}

vector<vector<string>> CSVParser::parseFile(const string & filename)
{
	ifstream in(filename);
	return parse(in);
}
