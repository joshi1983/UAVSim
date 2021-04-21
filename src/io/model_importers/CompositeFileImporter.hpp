#ifndef COMPOSITE_FILE_IMPORTER_HEADER
#define COMPOSITE_FILE_IMPORTER_HEADER
#include "FileImporter.hpp"
#include <vector>

class CompositeFileImporter: public FileImporter
{
	private:
		std::vector<FileImporter*> importers;
	public:
		CompositeFileImporter();
		virtual ~CompositeFileImporter();
		virtual bool supportsFileExtension(const std::string & filename) const override;
		virtual GroupNode* load(const std::string & filename) const override;
};

#endif
