#ifndef STRING_UTILS_HEADER_INCLUDED
#define STRING_UTILS_HEADER_INCLUDED
#include <string>

std::string trim(const std::string & s);
std::string toLower(const std::string &s);
void convertToWCharString(const char * from, wchar_t * result);

#endif
