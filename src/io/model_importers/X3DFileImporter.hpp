#ifndef X3D_FILE_IMPORTER_HEADER
#define X3D_FILE_IMPORTER_HEADER
#include "FileImporter.hpp"

class X3DFileImporter: public FileImporter
{
	public:
		virtual GroupNode* load(const std::string & filename) const override;
};

#endif
