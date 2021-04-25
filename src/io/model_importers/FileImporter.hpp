#ifndef FILE_IMPORTER_HPP
#define FILE_IMPORTER_HPP
#include <istream>
#include <string>
#include "../../models/GroupNode.hpp"

class FileImporter {
    private:
        const std::string fileExtension;
    protected:
        FileImporter(const char * fileExtension);
	public:
	    virtual ~FileImporter();
	    virtual bool supportsFileExtension(const std::string & filename) const;
		virtual GroupNode* load(const std::string & filename) const = 0;
};

#endif
