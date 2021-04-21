#include "CompositeFileImporter.hpp"
#include "X3DFileImporter.hpp"
#include "WRLFileImporter.hpp"

using namespace std;

CompositeFileImporter::CompositeFileImporter(): FileImporter("")
{
	importers.push_back(new X3DFileImporter());
	importers.push_back(new WRLFileImporter());
}

CompositeFileImporter::~CompositeFileImporter()
{
    for (auto im = importers.begin(); im != importers.end(); im++)
        delete *im;
}

bool CompositeFileImporter::supportsFileExtension(const string & filename) const
{
	for (auto importer = importers.begin(); importer != importers.end(); importer++)
	{
		if ((*importer)->supportsFileExtension(filename))
			return true;
	}
	return false;
}

GroupNode* CompositeFileImporter::load(const string & filename) const
{
	for (auto importer = importers.begin(); importer != importers.end(); importer++)
	{
		if ((*importer)->supportsFileExtension(filename))
			return (*importer)->load(filename);
	}
	return NULL; // unable to load.
}
