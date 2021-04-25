#ifndef UAV_SIM_BINARY_FILE_IMPORTER_HEADER
#define UAV_SIM_BINARY_FILE_IMPORTER_HEADER
#include "FileImporter.hpp"

class UAVSimBinaryFileImporter: public FileImporter
{
	public:
		UAVSimBinaryFileImporter();
		virtual ~UAVSimBinaryFileImporter();
		virtual GroupNode* load(const std::string & filename) const override;
};

#endif