#include "Config.hpp"
#include "../Files.hpp"
#include "../../lib/rapidjson/filereadstream.h"
#include "../../lib/rapidjson/error/en.h"
#include <iostream>
#include <string>
using namespace std;
using namespace rapidjson;

UAVSimConfig UAVSimConfig::config;

UAVSimConfig::UAVSimConfig()
{
}

void UAVSimConfig::load()
{
    string filename = getAbsolutePathForFilename("data\\settings.json");
    if (fileExists(filename))
    {
        char buffer[65536];
        FILE *pFile = fopen(filename.c_str(), "rb");
        FileReadStream is(pFile, buffer, sizeof(buffer));
        doc.ParseStream<0, UTF8<>, FileReadStream>(is);
        if (doc.HasParseError())
            cerr << "Parse failed for " << filename << " with message: " << GetParseError_En(doc.GetParseError()) << endl;
    }
    else
        cerr << filename << " not found so default settings will be used." << endl;
}
