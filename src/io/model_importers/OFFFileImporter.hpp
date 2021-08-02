#ifndef OFF_FILE_IMPORTER_HEADER_INCLUDED
#define OFF_FILE_IMPORTER_HEADER_INCLUDED
#include "FileImporter.hpp"

class OFFFileImporter: public FileImporter
{
	public:
		OFFFileImporter();
		virtual ~OFFFileImporter();
        static void addTriangles(const std::vector<unsigned int>& indexes, const std::vector<Vertex>& vertices, std::vector<Triangle> &triangles);
		virtual GroupNode* load(const std::string & filename) const override;
};

#endif
