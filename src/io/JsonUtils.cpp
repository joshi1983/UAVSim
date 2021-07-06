#include "JsonUtils.hpp"
#include <sstream>
#include "../lib/rapidjson/stringbuffer.h"
#include "../lib/rapidjson/prettywriter.h"

void rapidJsonDocumentToString(const rapidjson::Document& inputDoc, std::string& result)
{
    rapidjson::StringBuffer strbuf;
    strbuf.Clear();

    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    inputDoc.Accept(writer);

    result = strbuf.GetString();
}

void vector3DToRapidJsonObject(const Vector3D& pos, rapidjson::Value& result, rapidjson::Document::AllocatorType& allocator)
{
    result.SetObject();
    result.AddMember("x", rapidjson::Value().SetDouble(pos.x), allocator);
    result.AddMember("y", rapidjson::Value().SetDouble(pos.y), allocator);
    result.AddMember("z", rapidjson::Value().SetDouble(pos.z), allocator);
}

void jsonObjectToVector3D(rapidjson::Value& input, Vector3D& result)
{
    if (input.HasMember("x") && input["x"].IsNumber())
        result.x = input["x"].GetDouble();
    if (input.HasMember("y") && input["y"].IsNumber())
        result.y = input["y"].GetDouble();
    if (input.HasMember("z") && input["z"].IsNumber())
        result.z = input["z"].GetDouble();
}
