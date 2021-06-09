#include "TriangleFilterFactoryTest.hpp"
#include "../models/triangle_filters/TriangleFilterFactory.hpp"
#include "../lib/rapidjson/document.h"
#include "../lib/rapidjson/pointer.h"
#include "../lib/rapidjson/error/en.h"
#include <iostream>
using namespace std;

void testCubeVertexFiltersMadeByFactory(UnitTest& unitTest)
{
    const string content = "{\"blade2\": { \"miny\": 3.83,\"maxy\": 3.95,\"maxz\": 0.18,\"minz\": -0.18 } }";
    rapidjson::Document doc;
    doc.Parse<0>(content.c_str());
    if (doc.HasParseError())
        cerr << "Parse failed with message: " << GetParseError_En(doc.GetParseError()) << endl;

    // parse content.
    // run createTriangleFilterFrom.
    rapidjson::Value* value = rapidjson::Pointer("/blade2").Get(doc);
    TriangleFilter * tf = createTriangleFilterFrom(value);
    Triangle t;
    t.vertices[0] = Vertex(0, 3.9, 0);
    t.vertices[1] = Vertex(0, 3.9, 0);
    t.vertices[2] = Vertex(0, 3.9, 0);

    // check that a few points are and other points are not in the cube.
    unitTest.assertTrue(tf->isIncluded(t), "Triangle expected to be included");

    t.vertices[1] = Vertex(0, 3.9, 0.2);
    unitTest.assertTrue(!tf->isIncluded(t), "Triangle expected to not be included");

    t.vertices[1] = Vertex(0, 3.9, -0.2);
    unitTest.assertTrue(!tf->isIncluded(t), "Triangle expected to not be included");
}

TriangleFilterFactoryTest::TriangleFilterFactoryTest(): UnitTest("TriangleFilterFactoryTest")
{
    testFunctions.push_back(make_pair("CubeVertexFilter", testCubeVertexFiltersMadeByFactory));
}


