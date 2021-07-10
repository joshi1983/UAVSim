#include "UAVModelExporter.hpp"
#include "../Files.hpp"
using namespace std;

UAVModelExporter::UAVModelExporter(const char * fileExtension): fileExtension(fileExtension)
{

}

bool UAVModelExporter::supportsFileExtension(const string & filename) const
{
	return getFileExtension(filename) == fileExtension;
}