#include "Files.hpp"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <windows.h>
using namespace std;

const char* programPath = nullptr; // cached value for getProgramPath().

const char* getProgramPath()
{
    // if not calculated yet, calculate it.
    if (programPath == nullptr)
    {
        // implementation was copied and adapted from:
        // https://stackoverflow.com/questions/1528298/get-path-of-executable
        char ownPth[MAX_PATH];

         // When NULL is passed to GetModuleHandle, the handle of the exe itself is returned
         HMODULE hModule = GetModuleHandle(NULL);
         if (hModule != NULL)
         {
             // Use GetModuleFileName() with module handle to get the path
             GetModuleFileName(hModule, ownPth, (sizeof(ownPth)));
             char * result = new char[strlen(ownPth) + 1];
             strcpy(result, ownPth);
             programPath = result;
         }
         else
         {
             cerr << "Module handle is NULL" << endl ;
         }
    }
    return programPath;
}

string getFileExtension(const string & filename)
{
	string::size_type idx;
	idx = filename.rfind('.');
	if (idx != string::npos)
		return filename.substr(idx+1);
	return "";
}

bool fileExists(const string & filename)
{
	ifstream ifile;
	ifile.open(filename);
	return (bool)ifile;
}

string getAbsolutePathForFilename(const char * filename)
{
    const char* result = getProgramPath();
    return getAbsolutePathForFilename(result, filename);
}

string getAbsolutePathForFilename(const char * programPath, const char * filename)
{
    // if filename is already an absolute path, just return it.
    if (strlen(filename) > 1 && filename[1] == ':')
        return string(filename);
    string result(programPath);
    if (result.find("\\") == string::npos)
        replace( result.begin(), result.end(), '/', '\\');
    vector<string> directoryEndingsToRemove = {
        "src\\bin\\Debug\\",
        "src\\bin\\Release\\",
        "bin\\",
        "\\"
    };
    for (const string& ending: directoryEndingsToRemove)
    {
        size_t index = result.rfind(ending);
        if (index != string::npos)
        {
            result = result.substr(0, index);
            break;
        }
    }
    if (result[result.length() - 1] != '\\')
        result += '\\';

    return result + filename;
}

void copy_file(const std::string & from, const std::string & to)
{
    // FIXME: use c++17's filesystem library.
    ifstream  src(from, std::ios::binary);
    ofstream  dst(to,   std::ios::binary);

    dst << src.rdbuf();
}

/*
Useful for converting between little-endian and big-endian.
*/
void reverseByteOrder(int8_t *buff, unsigned int byteCount)
{
	unsigned int halfLen = byteCount / 2;
	for (unsigned int i = 0; i < halfLen; i++)
	{
		unsigned int swapIndex = byteCount - i - 1;
		int8_t temp = buff[i];
		buff[i] = buff[swapIndex];
		buff[swapIndex] = temp;
	}
}
