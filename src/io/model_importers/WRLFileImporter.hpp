#ifndef WRL_FILE_IMPORTER_HEADER
#define WRL_FILE_IMPORTER_HEADER
#include "FileImporter.hpp"

class WRLFileImporter: public FileImporter
{
	public:
		WRLFileImporter();
		virtual ~WRLFileImporter();
		virtual GroupNode* load(const std::string & filename) const override;
};

#endif