#ifndef JSON_UTILS_HEADER_INCLUDED
#define JSON_UTILS_HEADER_INCLUDED
#include "../lib/rapidjson/document.h"
#include "../models/Vector3D.hpp"

void rapidJsonDocumentToString(const rapidjson::Document& input, std::string& result);
void vector3DToRapidJsonObject(const Vector3D& pos, rapidjson::Value& result, rapidjson::Document::AllocatorType& allocator);
void jsonObjectToVector3D(rapidjson::Value& input, Vector3D& result);
double getDefaultedDouble(rapidjson::Value& input, const std::string & key, double defaultValue);

#endif
