#include "FileExporter.hpp"
#include "../Files.hpp"
using namespace std;

FileExporter::FileExporter(const char * fileExtension): fileExtension(fileExtension)
{

}

FileExporter::~FileExporter()
{
}

bool FileExporter::supportsFileExtension(const string & filename) const
{
	return getFileExtension(filename) == fileExtension;
}
