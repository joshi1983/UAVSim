#include "Files.hpp"
#include <fstream>
using namespace std;

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
