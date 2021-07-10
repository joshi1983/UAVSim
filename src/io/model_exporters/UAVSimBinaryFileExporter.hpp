#ifndef UAV_SIM_BINARY_FILE_EXPORTER_HEADER
#define UAV_SIM_BINARY_FILE_EXPORTER_HEADER
#include "FileExporter.hpp"
#include <fstream>
#include <vector>

class UAVSimBinaryFileExporter: public FileExporter
{
    public:
        UAVSimBinaryFileExporter();
	    virtual ~UAVSimBinaryFileExporter();
		virtual void save(const GroupNode& groupNode, const std::string & filename) const;
		static void write(const std::vector<Triangle>& triangles,  std::vector<unsigned char> & out);
};

#endif
