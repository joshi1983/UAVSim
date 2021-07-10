#ifndef UAVMODEL_EXPORTER_HEADER_INCLUDED
#define UAVMODEL_EXPORTER_HEADER_INCLUDED
#include <string>
#include "../../models/UAVModel.hpp"
#include <vector>

class UAVModelExporter
{
	private:
        const std::string fileExtension;
    protected:
        UAVModelExporter(const char * fileExtension);
	public:
		virtual bool supportsFileExtension(const std::string & filename) const;
		virtual void write(const UAVModel* model, std::vector<unsigned char> & out) const = 0;
};

#endif
