#ifndef FILES_HEADER_INCLUDED
#define FILES_HEADER_INCLUDED
#include <string>

std::string getFileExtension(const std::string & filename);
bool fileExists(const std::string & filename);
void setProgramPath(const char * programPath);
std::string getAbsolutePathForFilename(const char * filename);
std::string getAbsolutePathForFilename(const char * programPath, const char * filename);

#endif
