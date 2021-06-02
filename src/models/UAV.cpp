#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include <string>
#include <iostream>
#include "../io/Files.hpp"
#include "../io/model_importers/CompositeFileImporter.hpp"
#include "../io/model_exporters/UAVSimBinaryFileExporter.hpp"
#include "../io/config/Config.hpp"
#include "GroupNode.hpp"
#include "UAV.hpp"
#include "ColouredTriangleSet.hpp"
using namespace std;

vector<ColouredTriangleSet> shapes;

void processTransformation(vector<Triangle>& triangles)
{
    UAVSimConfig& c = UAVSimConfig::config;
    double scale = c.getDefaultedDouble("/uav/scale", 10);
    double tx = c.getDefaultedDouble("/uav/translate/x", 0);
    double ty = c.getDefaultedDouble("/uav/translate/y", 0);
    double tz = c.getDefaultedDouble("/uav/translate/z", 0);

    for (auto t = triangles.begin(); t != triangles.end(); t++)
    {
        for (int vertexIndex = 0; vertexIndex < 3; vertexIndex++)
        {
            t->vertices[vertexIndex] = t->vertices[vertexIndex] * scale;
            t->vertices[vertexIndex].x += tx;
            t->vertices[vertexIndex].y += ty;
            t->vertices[vertexIndex].z += tz;
        }
        t->updateNormal();
    }
}

UAV::UAV()
{
    string filename = getAbsolutePathForFilename("data\\models\\cache\\uav.uavsim");
    bool cacheUsed = fileExists(filename);
    if (!cacheUsed)
        filename = getAbsolutePathForFilename("data\\models\\uav.wrl");
    CompositeFileImporter importer;
    GroupNode * group = importer.load(filename);
    if (group == NULL)
        cerr << "Unable to load from 3D file: " << filename << endl;
    else
    {
        if (!cacheUsed)
        {
            UAVSimBinaryFileExporter saver;
            filename = getAbsolutePathForFilename("data\\models\\cache\\uav.uavsim");
            saver.save(*group, filename);
        }
        vector<Triangle> triangles = group->getTriangles();
        delete group;
        processTransformation(triangles);

        // white part.
        shapes.push_back(ColouredTriangleSet(1, 1, 1));
        shapes.push_back(ColouredTriangleSet(1, 1, 1));
        shapes.push_back(ColouredTriangleSet(1, 1, 1));

        const double whiteMaxY = 3.7;
        const double blade1MaxY = 3.85;
        for (auto t = triangles.begin(); t != triangles.end(); t++)
        {
            double maxY = -99999;
            for (unsigned int vIndex = 0; vIndex < 3; vIndex++)
            {
                maxY = max(maxY, t->vertices[vIndex].y);
            }
            if (maxY <= whiteMaxY)
                shapes[0].triangles.push_back(*t); // main body.
            else if (maxY <= blade1MaxY)
                shapes[1].triangles.push_back(*t); // lower propeller
            else
                shapes[2].triangles.push_back(*t); // upper propeller
        }
	}
}

void UAV::draw(const AnimationState & animationState, double yOffset) const
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		glTranslated(0, animationState.cameraY + yOffset, animationState.cameraZ - 3.0);
		shapes[0].draw();
		glPushMatrix();
			glRotated(animationState.bladeAngle, 0, 1, 0);
			shapes[1].draw();
		glPopMatrix();
		glPushMatrix();
			glRotated(-animationState.bladeAngle, 0, 1, 0);
			shapes[2].draw();
		glPopMatrix();
	glPopMatrix();
}
