#ifndef PHYSICS_API_HANDLERS_HEADER_INCLUDED
#define PHYSICS_API_HANDLERS_HEADER_INCLUDED
#include <string>
#include "../../../lib/rapidjson/document.h"

std::string getAllPhysicsData();
std::string handleAPIPostPhysicsRequest(rapidjson::Document &doc);
std::string handleAPIPostPhysicsTimeChangeRequest(rapidjson::Document &doc);

#endif
