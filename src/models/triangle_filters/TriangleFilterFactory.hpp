#ifndef TRIANGLE_FILTER_FACTORY_HEADER_INCLUDED
#define TRIANGLE_FILTER_FACTORY_HEADER_INCLUDED
#include "IntersectionVertexFilter.hpp"
#include "UnionVertexFilter.hpp"
#include "VertexFilter.hpp"
#include "TriangleFilter.hpp"
#include "../../lib/rapidjson/pointer.h"

TriangleFilter * createTriangleFilterFrom(const rapidjson::Value* val);

#endif
