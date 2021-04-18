#ifndef FILE_IMPORTER_HPP
#define FILE_IMPORTER_HPP
#include <istream>
#include <string>
#include "../../models/GroupNode.hpp"

class FileImporter {
	public:
		virtual GroupNode* load(const std::string & filename) const = 0;
};

#endif
