#ifndef OSM_FILE_IMPORTER_HEADER
#define OSM_FILE_IMPORTER_HEADER
#include "FileImporter.hpp"

class OSMFileImporter: public FileImporter
{
	public:
		OSMFileImporter();
		virtual ~OSMFileImporter();
		virtual GroupNode* load(const std::string & filename) const override;
};

#endif