#include "X3DFileImporter.hpp"
#include "X3D/ElementProcessors.hpp"

using namespace X3D;

GroupNode* X3DFileImporter::load(const std::string & filename) const
{
	TiXmlDocument doc;
	doc.LoadFile(filename.c_str());
	return (GroupNode*)getModelNodeFromGroup(*doc.RootElement());
}
