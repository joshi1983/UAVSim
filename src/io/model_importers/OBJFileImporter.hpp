#ifndef OBJ_FILE_IMPORTER_HEADER
#define OBJ_FILE_IMPORTER_HEADER
#include "FileImporter.hpp"

class OBJFileImporter: public FileImporter
{
	public:
		OBJFileImporter();
		virtual ~OBJFileImporter();
		virtual GroupNode* load(const std::string & filename) const override;
};

#endif