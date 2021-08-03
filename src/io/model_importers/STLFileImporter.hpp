#ifndef STL_FILE_IMPORTER_HEADER_INCLUDED
#define STL_FILE_IMPORTER_HEADER_INCLUDED
#include "FileImporter.hpp"

class STLFileImporter: public FileImporter
{
	public:
		STLFileImporter();
		virtual ~STLFileImporter();
		virtual GroupNode* load(const std::string & filename) const override;	
};

#endif