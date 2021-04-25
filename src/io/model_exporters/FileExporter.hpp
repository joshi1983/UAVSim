#ifndef FILE_EXPORTER_HPP_INCLUDED
#define FILE_EXPORTER_HPP_INCLUDED
#include <istream>
#include <string>
#include "../../models/GroupNode.hpp"

class FileExporter {
    private:
        const std::string fileExtension;
    protected:
        FileExporter(const char * fileExtension);
	public:
	    virtual ~FileExporter();
	    virtual bool supportsFileExtension(const std::string & filename) const;
		virtual void save(const GroupNode& groupNode, const std::string & filename) const = 0;
};

#endif
