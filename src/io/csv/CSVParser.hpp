#ifndef CSV_PARSER_HEADER_INCLUDED
#define CSV_PARSER_HEADER_INCLUDED
#include <vector>
#include <string>
#include <istream>

class CSVParser
{
	private:
		char delimiter;
		bool trimValues;
		bool delimitersInQuotes;
		bool processEscapeCharacters;
		std::string sanitizeValue(const std::string & value) const;
	public:
		CSVParser(const char delimiter = ',', const bool trimValues = false, const bool delimitersInQuotes = true, const bool processEscapeCharacters = true);
		std::vector<std::vector<std::string>> parse(std::istream & in);
		std::vector<std::vector<std::string>> parseFile(const std::string & filename);
};

#endif
