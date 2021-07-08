#ifndef STRING_UTILS_HEADER_INCLUDED
#define STRING_UTILS_HEADER_INCLUDED
#include <string>
#include <vector>
#include <tchar.h>

std::string trim(const std::string & s);
std::string toLower(const std::string &s);
void convertToWCharString(const char * from, wchar_t * result);
void convertToTCharString(const char * from, TCHAR * result);
std::string simplifyWhitespaces(const std::string &s);
void tokenize(std::string const &str, const char delim,
            std::vector<std::string> &out);
void findAndReplaceAll(std::string & data, std::string toSearch, std::string replaceStr);

#endif
