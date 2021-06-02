#include "Config.hpp"
#include "../Files.hpp"
#include "../../lib/rapidjson/filereadstream.h"
#include "../../lib/rapidjson/error/en.h"
#include "../../lib/rapidjson/pointer.h"
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

bool UAVSimConfig::getDefaultedBool(string path, bool defaultedValue) const
{
    UAVSimConfig& c = UAVSimConfig::config;
    rapidjson::Value* a =  rapidjson::Pointer(path.c_str()).Get(c.doc);
    if (a != nullptr && a->IsBool())
        return a->GetBool();
    else
        return defaultedValue;
}

double UAVSimConfig::getDefaultedDouble(string path, double defaultedValue) const
{
    UAVSimConfig& c = UAVSimConfig::config;
    rapidjson::Value* a =  rapidjson::Pointer(path.c_str()).Get(c.doc);
    if (a != nullptr && a->IsDouble())
        return a->GetDouble();
    else
        return defaultedValue;
}
