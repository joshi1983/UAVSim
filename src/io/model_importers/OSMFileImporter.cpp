#include "OSMFileImporter.hpp"
#include "../../lib/TinyXML/tinyxml.h"

OSMFileImporter::OSMFileImporter(): FileImporter("osm")
{
	
}

OSMFileImporter::~OSMFileImporter()
{
}

GroupNode* OSMFileImporter::load(const std::string & filename) const
{
	// read file contents.
	TiXmlDocument doc;
    doc.LoadFile(filename.c_str());
	GroupNode * result = nullptr;

	return result;
}
