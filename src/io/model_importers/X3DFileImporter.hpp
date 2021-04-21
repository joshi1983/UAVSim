#ifndef X3D_FILE_IMPORTER_HEADER
#define X3D_FILE_IMPORTER_HEADER
#include "FileImporter.hpp"
#include "../../lib/TinyXML/tinyxml.h"

class X3DFileImporter: public FileImporter
{
	public:
		X3DFileImporter();
		virtual ~X3DFileImporter();
		virtual GroupNode* load(const std::string & filename) const override;

		static GroupNode* loadFrom(const TiXmlElement & scene);
		static GroupNode* loadFromContent(const std::string & content);
};

#endif
