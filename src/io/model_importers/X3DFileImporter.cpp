#include "X3DFileImporter.hpp"
#include "X3D/ElementProcessors.hpp"
#include <fstream>

using namespace std;
using namespace X3D;

X3DFileImporter::X3DFileImporter(): FileImporter("x3d")
{

}

X3DFileImporter::~X3DFileImporter()
{
}

GroupNode* X3DFileImporter::loadFrom(const TiXmlElement & scene)
{
	return (GroupNode*)getModelNodeFromGroup(scene);
}

GroupNode* X3DFileImporter::loadFromContent(const string & content)
{
	TiXmlDocument doc;
    doc.Parse(content.c_str(), 0, TIXML_ENCODING_UTF8);
	return loadFrom(*doc.RootElement());
}

GroupNode* X3DFileImporter::load(const string & filename) const
{
    ifstream ifs(filename);
    string content( (istreambuf_iterator<char>(ifs) ),
                       (istreambuf_iterator<char>()    ) );
    return loadFromContent(content);
}
