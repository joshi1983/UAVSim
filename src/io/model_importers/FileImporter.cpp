#include "FileImporter.hpp"
#include "../Files.hpp"
using namespace std;

FileImporter::FileImporter(const char * fileExtension): fileExtension(fileExtension)
{

}

FileImporter::~FileImporter()
{
}

bool FileImporter::supportsFileExtension(const string & filename) const
{
	return getFileExtension(filename) == fileExtension;
}
