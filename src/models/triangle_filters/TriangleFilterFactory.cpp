#include "ConfiguredTriangleFilter.hpp"
#include "../../io/stringUtils.hpp"
#include "../../lib/rapidjson/pointer.h"
#include <limits>
#include <map>
#include "CubeVertexFilter.hpp"
#include "IntersectionVertexFilter.hpp"
#include "CylinderVertexFilter.hpp"
using namespace rapidjson;
using namespace std;

bool needsCubeVertexFilter(const Value* obj)
{
	for (auto& i: obj->GetObject())
	{
		string key = toLower(i.name.GetString());
		if ((key.rfind("min", 0) == 0 || key.rfind("max", 0) == 0) && key.length() == 4 && i.value.IsDouble())
            return true;
	}
	return false;
}

VertexFilter * createCubeVertexFilterFrom(const Value* obj)
{
	map<string, double> ranges;
	ranges["minx"] = ranges["miny"] = ranges["minz"] = numeric_limits<double>::max();
	ranges["maxx"] = ranges["maxy"] = ranges["maxz"] = -numeric_limits<double>::max();
	for (auto& i: obj->GetObject())
	{
		string key = toLower(i.name.GetString());
		if (i.value.IsDouble())
            ranges[key] = i.value.GetDouble();
	}
	return new CubeVertexFilter(ranges["minx"], ranges["miny"], ranges["minz"],
		ranges["maxx"], ranges["maxy"], ranges["maxz"]);
}

bool isValidCylinder(const Value* obj)
{
    if (!obj->HasMember("radius") || !obj->HasMember("from") || !obj->HasMember("to"))
        return false;
    if (!obj->FindMember("radius")->value.IsDouble() ||
        !obj->FindMember("from")->value.IsObject() ||
        !obj->FindMember("to")->value.IsObject())
        return false;
    return true;
}

void getCoordinates(const Value* obj, double &x, double &y, double&z)
{
    x = obj->FindMember("x")->value.GetDouble();
    y = obj->FindMember("y")->value.GetDouble();
    z = obj->FindMember("z")->value.GetDouble();
}

VertexFilter* createCylinderVertexFilter(const Value* obj)
{
    double radius = obj->FindMember("radius")->value.GetDouble();
    double fromX, fromY, fromZ;
    double toX, toY, toZ;
    getCoordinates(&obj->FindMember("from")->value, fromX, fromY, fromZ);
    getCoordinates(&obj->FindMember("to")->value, toX, toY, toZ);
    return new CylinderVertexFilter(radius, fromX, fromY, fromZ, toX, toY, toZ);
}

VertexFilter* createVertexFilterFrom(const Value* obj)
{
    vector<VertexFilter*> filters;
    if (needsCubeVertexFilter(obj))
        filters.push_back(createCubeVertexFilterFrom(obj));
    if (obj->HasMember("type") && obj->FindMember("type")->value.IsString())
    {
        string type = obj->FindMember("type")->value.GetString();
        if (type == "cylinder" && isValidCylinder(obj))
        {
            filters.push_back(createCylinderVertexFilter(obj));
        }
    }
	VertexFilter * intersectedFilters = nullptr;
    if (filters.size() == 1)
        intersectedFilters = filters[0];
    else if (filters.size() > 1)
        intersectedFilters = new IntersectionVertexFilter(filters);

	if (obj->HasMember("union") && obj->FindMember("union")->value.IsArray())
	{
		vector<VertexFilter*> unionFilters;
		for (auto& i: obj->FindMember("union")->value.GetArray())
			unionFilters.push_back(createVertexFilterFrom(&i));
		if (unionFilters.size() > 0)
		{
			if (intersectedFilters != nullptr)
			{
				unionFilters.push_back(intersectedFilters);
			}
			if (unionFilters.size() == 1)
				return unionFilters[0];
			else
				return new UnionVertexFilter(unionFilters);
		}
	}
    if (intersectedFilters != nullptr)
        return intersectedFilters;
    else
        return createCubeVertexFilterFrom(obj); // an all-inclusive filter.
}

TriangleFilter * createTriangleFilterFrom(const Value* val)
{
	VertexFilter *vf = createVertexFilterFrom(val);
	return new TriangleFilter(3, vf);
}