#include "WRLFileImporter.hpp"
#include "WRL/WRLUtils.hpp"
#include "X3DFileImporter.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

// Copied from http://www.martinbroadhurst.com/read-a-file-into-a-string-in-c.html
string readAllText(const string& path) {
    std::ifstream in(path);
    if (in) {
        ostringstream ss;
        ss << in.rdbuf(); // reading data
        return ss.str();
    }
    return "";
}

WRLFileImporter::WRLFileImporter(): FileImporter("wrl")
{

}

WRLFileImporter::~WRLFileImporter()
{
}

GroupNode* WRLFileImporter::load(const std::string & filename) const
{
	// read file contents.
	string content = readAllText(filename);
	TiXmlDocument * doc = vrmlToX3DDocument(content);
	GroupNode * result = NULL;
	try {
        result = X3DFileImporter::loadFrom(*doc->RootElement());
	}
	catch (InvalidVRMLElementNameException & badTag)
	{
	    cerr << "Unable to load file " << filename << " because an invalid VRML element was found.";
	    cerr << "Details: " << badTag.what() << endl;
	}
	delete doc;
	return result;
}
