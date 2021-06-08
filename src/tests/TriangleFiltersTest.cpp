#include "TriangleFiltersTest.hpp"
#include "../models/triangle_filters/CubeVertexFilter.hpp"
#include "../models/triangle_filters/SphereVertexFilter.hpp"
#include "../models/triangle_filters/CylinderVertexFilter.hpp"
#include "../models/triangle_filters/IntersectionVertexFilter.hpp"
#include "../models/triangle_filters/UnionVertexFilter.hpp"
#include "../models/triangle_filters/TriangleFilter.hpp"
using namespace std;

void testCubeVertexFilters(UnitTest& unitTest)
{
    CubeVertexFilter cf(-3, -2, -1, 1, 2, 3);
    Vertex v;
    for (v.x = -2.99; v.x < 1; v.x += 1)
        for (v.y = -1.99; v.y < 2; v.y += 1)
            for (v.z = -0.99; v.z < 3; v.z += 1)
                unitTest.assertTrue(cf.isIncluded(v), string("Expected to include ") + v.str());
    v.x = -3.01;
    unitTest.assertTrue(!cf.isIncluded(v), string("Expected to not include ") + v.str());
    v.x = 1.01;
    unitTest.assertTrue(!cf.isIncluded(v), string("Expected to not include ") + v.str());
    v.x = 0;
    v.y = -2.01;
    unitTest.assertTrue(!cf.isIncluded(v), string("Expected to not include ") + v.str());
    v.y = 2.01;
    unitTest.assertTrue(!cf.isIncluded(v), string("Expected to not include ") + v.str());
    v.y = 0;
    v.z = -1.01;
    unitTest.assertTrue(!cf.isIncluded(v), string("Expected to not include ") + v.str());
    v.z = 3.01;
    unitTest.assertTrue(!cf.isIncluded(v), string("Expected to not include ") + v.str());
}

void testSphereVertexFilters(UnitTest& unitTest)
{
    SphereVertexFilter sf(1, 2, 3, 2);
    Vertex v;
    v.x = 1;
    v.y = 2;
    v.z = 3;
    for (v.x = -0.9; v.x < 3; v.x += 1)
        unitTest.assertTrue(sf.isIncluded(v), string("Expected to include ") + v.str());
    v.x = 1;
    for (v.y = 0.1; v.y < 4; v.y += 1)
        unitTest.assertTrue(sf.isIncluded(v), string("Expected to include ") + v.str());
    v.y = 2;
    for (v.z = 1.1; v.z < 5; v.z += 1)
        unitTest.assertTrue(sf.isIncluded(v), string("Expected to include ") + v.str());

    v.x = 0;
    v.y = 0;
    v.z = 3;
    unitTest.assertTrue(!sf.isIncluded(v), string("Expected to not include ") + v.str());
}

void testCylinderVertexFilters(UnitTest& unitTest)
{
    CylinderVertexFilter cvf(2, 1, 2, 3, 0, 0, 1);
    Vertex v;
    v.x = 1;
    v.y = 2;
    for (v.z = -5; v.z < 5; v.z += 1)
    {
        for (v.x = 0.1; v.x <1.9; v.x++)
            for (v.y = 1.1; v.y <2.9; v.y++)
                unitTest.assertTrue(cvf.isIncluded(v), string("Expected to include ") + v.str());
    }
    v.x = 0;
    v.y = 0;
    v.z = 0;
    unitTest.assertTrue(!cvf.isIncluded(v), string("Expected to not include ") + v.str());
}

void testIntersectionVertexFilters(UnitTest& unitTest)
{
    CubeVertexFilter *cf = new CubeVertexFilter(-3, -2, -1, 1, 2, 3);
    CubeVertexFilter *cf2 = new CubeVertexFilter(0, 0, 0, 3, 3, 3);
    IntersectionVertexFilter ivf(vector<VertexFilter*>({cf, cf2}));
    Vertex v;

    for (v.x = -4.99; v.x < 0; v.x += 1)
        for (v.y = -4.99; v.y < 0; v.y += 1)
            for (v.z = -4.99; v.z < 0; v.z += 1)
                unitTest.assertTrue(!ivf.isIncluded(v), string("Expected to not include ") + v.str());
    for (v.x = 0.1; v.x < 1; v.x += 1)
        for (v.y = 0.1; v.y < 2; v.y += 1)
            for (v.z = 0.1; v.z < 3; v.z += 1)
                unitTest.assertTrue(ivf.isIncluded(v), string("Expected to include ") + v.str());
}

void testUnionVertexFilters(UnitTest& unitTest)
{
    CubeVertexFilter *cf = new CubeVertexFilter(-3, -2, -1, 1, 2, 3);
    CubeVertexFilter *cf2 = new CubeVertexFilter(0, 0, 0, 3, 3, 3);
    UnionVertexFilter uvf(vector<VertexFilter*>({cf, cf2}));
    Vertex v;

    for (v.x = -2.99; v.x < 1; v.x += 1)
        for (v.y = -1.99; v.y < 2; v.y += 1)
            for (v.z = -0.99; v.z < 3; v.z += 1)
                unitTest.assertTrue(uvf.isIncluded(v), string("Expected to include ") + v.str());
    for (v.x = 0.1; v.x < 3; v.x += 1)
        for (v.y = 0.1; v.y < 3; v.y += 1)
            for (v.z = 0.1; v.z < 3; v.z += 1)
                unitTest.assertTrue(uvf.isIncluded(v), string("Expected to include ") + v.str());
    for (v.x = 3.1; v.x < 5; v.x += 1)
        for (v.y = 3.1; v.y < 5; v.y += 1)
            for (v.z = 3.1; v.z < 5; v.z += 1)
                unitTest.assertTrue(!uvf.isIncluded(v), string("Expected to not include ") + v.str());
}

void testTriangleFilters(UnitTest& unitTest)
{
    CubeVertexFilter *cf = new CubeVertexFilter(0, 0, 0, 1, 1, 1);
    Vertex v1;
    v1.x = 0.5;
    v1.y = 0.5;
    v1.z = 0.5;
    Triangle t;
    t.vertices[0] = v1;
    t.vertices[1] = v1;
    t.vertices[2] = v1;
    TriangleFilter tf(3, cf);
    unitTest.assertTrue(tf.isIncluded(t), string("Expected to include ") + t.str());
    t.vertices[1].x = 1.1;
    unitTest.assertTrue(!tf.isIncluded(t), string("Expected to not include ") + t.str());
}


TriangleFiltersTest::TriangleFiltersTest(): UnitTest("TriangleFiltersTest")
{
    testFunctions.push_back(testCubeVertexFilters);
    testFunctions.push_back(testSphereVertexFilters);
    testFunctions.push_back(testCylinderVertexFilters);
    testFunctions.push_back(testIntersectionVertexFilters);
    testFunctions.push_back(testUnionVertexFilters);
    testFunctions.push_back(testTriangleFilters);
}
