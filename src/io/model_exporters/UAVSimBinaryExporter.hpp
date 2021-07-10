#ifndef UAVSIM_BINARY_EXPORTER_HEADER_INCLUDED
#define UAVSIM_BINARY_EXPORTER_HEADER_INCLUDED
#include "UAVModelExporter.hpp"

class UAVSimBinaryExporter: public UAVModelExporter
{
	public:
        UAVSimBinaryExporter();
		virtual void write(const UAVModel* model, std::vector<unsigned char> & out) const;

};

#endif
