#ifndef FILES_HEADER_INCLUDED
#define FILES_HEADER_INCLUDED
#include <string>
#include <fstream>
#include "../models/Vector3D.hpp"
#include "../models/Colour.hpp"

std::string getFileExtension(const std::string & filename);
bool fileExists(const std::string & filename);
std::string getAbsolutePathForFilename(const char * filename);
std::string getAbsolutePathForFilename(const char * programPath, const char * filename);
void copy_file(const std::string & from, const std::string & to);
void reverseByteOrder(int8_t *buff, unsigned int byteCount);
void readVector3DAscii(std::istream &in, Vector3D & result);
void readColourAscii(std::istream &in, Colour & result);

#endif
