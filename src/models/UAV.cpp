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
#include "triangle_filters/TriangleFilterFactory.hpp"
using namespace std;

vector<ColouredTriangleSet> shapes;
Vertex steeringPivot;
double servoPivotY;

void updateSteeringPivot(UAVSimConfig& c)
{
    steeringPivot.x = c.getDefaultedDouble("/steerable_assembly/pivot/x", 0);
    steeringPivot.y = c.getDefaultedDouble("/steerable_assembly/pivot/y", 3);
    steeringPivot.z = c.getDefaultedDouble("/steerable_assembly/pivot/z", 0);
    servoPivotY = c.getDefaultedDouble("/steerable_assembly/servo_pivot_y", 2.5);
}

void processTransformation(vector<Triangle>& triangles, UAVSimConfig& c)
{
    double scale = c.getDefaultedDouble("/scale", 10);
    double tx = c.getDefaultedDouble("/translate/x", 0);
    double ty = c.getDefaultedDouble("/translate/y", 0);
    double tz = c.getDefaultedDouble("/translate/z", 0);

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

TriangleFilter* createTriangleFilterFrom(const char * configPath, UAVSimConfig& c)
{
    rapidjson::Value* a = rapidjson::Pointer(configPath).Get(c.doc);
    if (a != nullptr)
        return createTriangleFilterFrom(a);
    else
        return nullptr;
}

string getCachedFilenameFrom(const string & fname)
{
    string lastPart;
    // get last index of '/'.
    int slashIndex1 = fname.rfind("/");
    // get last index of '\\'.
    int slashIndex2 = fname.rfind("\\");
    int index = max(slashIndex1, slashIndex2);
    if (index < 0)
        lastPart = fname;
    else
        lastPart = fname.substr(index + 1);
    index = lastPart.rfind(".");
    if (index >= 0)
        lastPart = lastPart.substr(0, index); // remove file extension.
    return string("data/models/cache/") + lastPart + ".uavsim";
}

bool loadTrianglesFromModel(UAVSimConfig& c, vector<Triangle>& triangles)
{
    string configuredFilename = c.getDefaultedString("/model", "data/models/uav.wrl");
    string cachedFilename = getCachedFilenameFrom(configuredFilename);
    string filename = getAbsolutePathForFilename(cachedFilename.c_str());
    bool cacheUsed = fileExists(filename);
    if (!cacheUsed)
        filename = getAbsolutePathForFilename(configuredFilename.c_str());
    CompositeFileImporter importer;
    GroupNode * group = importer.load(filename);
    if (group == NULL)
    {
        cerr << "Unable to load from 3D file: " << filename << endl;
        return false;
    }
    else
    {
        if (!cacheUsed)
        {
            UAVSimBinaryFileExporter saver;
            filename = getAbsolutePathForFilename(cachedFilename.c_str());
            saver.save(*group, filename);
        }
        triangles = group->getTriangles();
        delete group;
        return true;
    }
}

UAV::UAV()
{
    UAVSimConfig c;
    c.load(UAVSimConfig::config.getDefaultedString("/uav", "uav.json"));
    vector<Triangle> triangles;
    if (loadTrianglesFromModel(c, triangles))
    {
        cerr << "Loaded triangles: " << triangles.size() << endl;
        processTransformation(triangles, c);

        // white part.
        for (int i = 0; i < 8; i++)
            shapes.push_back(ColouredTriangleSet(1, 1, 1));

        updateSteeringPivot(c);

        rapidjson::Value* a = rapidjson::Pointer("/delete").Get(c.doc);
        if (a != nullptr)
        {
            // remove unneeded triangles so the loaded model is more efficient.
            TriangleFilter * deletableTriangleFilter = createTriangleFilterFrom(a);
            deletableTriangleFilter->removeFrom(triangles);
            delete deletableTriangleFilter;
        }

        TriangleFilter * blade1Filter = createTriangleFilterFrom("/steerable_assembly/blade1", c);
        TriangleFilter * blade2Filter = createTriangleFilterFrom("/steerable_assembly/blade2", c);
        TriangleFilter * steerableColumnFilter = createTriangleFilterFrom("/steerable_assembly/steerable_column", c);
        TriangleFilter * servo1Filter = createTriangleFilterFrom("/steerable_assembly/servo1_arm", c);
        TriangleFilter * servo2Filter = createTriangleFilterFrom("/steerable_assembly/servo2_arm", c);
        TriangleFilter * servo3Filter = createTriangleFilterFrom("/steerable_assembly/servo3_arm", c);
        TriangleFilter * servo4Filter = createTriangleFilterFrom("/steerable_assembly/servo4_arm", c);

        for (auto t = triangles.begin(); t != triangles.end(); t++)
        {
            double maxY = -99999;
            for (unsigned int vIndex = 0; vIndex < 3; vIndex++)
            {
                maxY = max(maxY, t->vertices[vIndex].y);
            }
            if (blade2Filter != nullptr && blade2Filter->isIncluded(*t))
                shapes[2].triangles.push_back(*t); // upper propeller
            else if (blade1Filter != nullptr && blade1Filter->isIncluded(*t))
                shapes[1].triangles.push_back(*t); // lower propeller
            else if (steerableColumnFilter != nullptr && steerableColumnFilter->isIncluded(*t))
                shapes[3].triangles.push_back(*t); // lower propeller
            else if (servo1Filter != nullptr && servo1Filter->isIncluded(*t))
                shapes[4].triangles.push_back(*t);
            else if (servo1Filter != nullptr && servo2Filter->isIncluded(*t))
                shapes[5].triangles.push_back(*t);
            else if (servo1Filter != nullptr && servo3Filter->isIncluded(*t))
                shapes[6].triangles.push_back(*t);
            else if (servo1Filter != nullptr && servo4Filter->isIncluded(*t))
                shapes[7].triangles.push_back(*t);
            else
                shapes[0].triangles.push_back(*t); // main body.
        }
	}
}

void UAV::draw(const AnimationState & animationState, double yOffset) const
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		glTranslated(0, animationState.cameraY + yOffset, animationState.cameraZ);
		shapes[0].draw();
		glPushMatrix();
            glTranslated(0, servoPivotY, 0);
            glRotated(animationState.steerAngle2 * 0.5, 1, 0, 0);
            glTranslated(0, -servoPivotY, 0);
            for (int i = 4; i < 6; i++)
                shapes[i].draw();
		glPopMatrix();
		glPushMatrix();
            glTranslated(0, servoPivotY, 0);
            glRotated(animationState.steerAngle1 * 0.5, 0, 0, 1);
            glTranslated(0, -servoPivotY, 0);
            for (int i = 6; i < 8; i++)
                shapes[i].draw();
		glPopMatrix();
		glPushMatrix();
            glTranslated(steeringPivot.x, steeringPivot.y, steeringPivot.z);
            glRotated(animationState.steerAngle1, 0, 0, 1);
            glRotated(animationState.steerAngle2, 1, 0, 0);
            glTranslated(-steeringPivot.x, -steeringPivot.y, -steeringPivot.z);
            shapes[3].draw();
            glPushMatrix();
                glRotated(animationState.bladeAngle, 0, 1, 0);
                shapes[1].draw();
            glPopMatrix();
            glPushMatrix();
                glRotated(-animationState.bladeAngle, 0, 1, 0);
                shapes[2].draw();
            glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}
