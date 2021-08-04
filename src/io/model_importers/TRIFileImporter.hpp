#ifndef TRI_FILE_IMPORTER_HEADER_INCLUDED
#define TRI_FILE_IMPORTER_HEADER_INCLUDED
#include "FileImporter.hpp"

class TRIFileImporter: public FileImporter
{
	public:
		TRIFileImporter();
		virtual ~TRIFileImporter();
		virtual GroupNode* load(const std::string & filename) const override;	
};

#endif