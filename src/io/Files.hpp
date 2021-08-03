#ifndef FILES_HEADER_INCLUDED
#define FILES_HEADER_INCLUDED
#include <string>

std::string getFileExtension(const std::string & filename);
bool fileExists(const std::string & filename);
std::string getAbsolutePathForFilename(const char * filename);
std::string getAbsolutePathForFilename(const char * programPath, const char * filename);
void copy_file(const std::string & from, const std::string & to);
void reverseByteOrder(int8_t *buff, unsigned int byteCount);

#endif
