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

void UAVSimConfig::load(const std::string & filename_)
{
    string filename = getAbsolutePathForFilename(filename_.c_str());
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

void UAVSimConfig::load()
{
    load("data\\settings.json");
}

bool UAVSimConfig::getDefaultedBool(string path, bool defaultedValue)
{
    rapidjson::Value* a =  rapidjson::Pointer(path.c_str()).Get(this->doc);
    if (a != nullptr && a->IsBool())
        return a->GetBool();
    else
        return defaultedValue;
}

double UAVSimConfig::getDefaultedDouble(string path, double defaultedValue)
{
    rapidjson::Value* a =  rapidjson::Pointer(path.c_str()).Get(doc);
    if (a != nullptr && a->IsNumber())
        return a->GetDouble();
    else
        return defaultedValue;
}

string UAVSimConfig::getDefaultedString(string path, string defaultedValue)
{
    rapidjson::Value* a =  rapidjson::Pointer(path.c_str()).Get(doc);
    if (a != nullptr && a->IsString())
        return a->GetString();
    else
        return defaultedValue;
}

int UAVSimConfig::getDefaultedInt(std::string path, int defaultedValue)
{
    rapidjson::Value* a =  rapidjson::Pointer(path.c_str()).Get(doc);
    if (a != nullptr && a->IsInt())
        return a->GetInt();
    else
        return defaultedValue;
}

