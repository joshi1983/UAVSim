#ifndef PLY_FILE_IMPORTER_HEADER_INCLUDED
#define PLY_FILE_IMPORTER_HEADER_INCLUDED
#include "FileImporter.hpp"

class PLYFileImporter: public FileImporter
{
	public:
		PLYFileImporter();
		virtual ~PLYFileImporter();
		virtual GroupNode* load(const std::string & filename) const override;
};

#endif
