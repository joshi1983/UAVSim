#include "FileImporter.hpp"
using namespace std;

FileImporter::FileImporter(const char * fileExtension): fileExtension(fileExtension)
{

}

FileImporter::~FileImporter()
{
}

string FileImporter::getFileExtension(const string & filename)
{
	string::size_type idx;
	idx = filename.rfind('.');
	if (idx != string::npos)
		return filename.substr(idx+1);
	return "";
}

bool FileImporter::supportsFileExtension(const string & filename) const
{
	return getFileExtension(filename) == fileExtension;
}
