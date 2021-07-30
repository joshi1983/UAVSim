#include "Files.hpp"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;

static string programPath;

void setProgramPath(const char * _programPath)
{
    programPath = _programPath;
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
    return getAbsolutePathForFilename(programPath.c_str(), filename);
}

string getAbsolutePathForFilename(const char * programPath, const char * filename)
{
    // if filename is already an absolute path, just return it.
    if (strlen(filename) > 1 && filename[1] == ':')
        return string(filename);
    string result(programPath);
    if (result.find("\\") == string::npos)
        replace( result.begin(), result.end(), '/', '\\');
    size_t index = result.rfind("src\\bin\\Debug\\");
    if (index != string::npos)
        result = result.substr(0, index);
    else
    {
        index = result.rfind("src\\bin\\Release\\");
        if (index != string::npos)
            result = result.substr(0, index);
        else
        {
            index = result.rfind("\\");
            if (index != string::npos)
                result = result.substr(0, index);
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
