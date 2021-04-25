#include "renderer.hpp"
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <algorithm>
#include <cmath>
#include "io/model_importers/CompositeFileImporter.hpp"
#include "io/model_exporters/UAVSimBinaryFileExporter.hpp"
#include "models/Triangle.hpp"
#include "models/ColouredTriangleSet.hpp"
#include "models/Texture.hpp"
#include "io/Files.hpp"
using namespace std;

vector<ColouredTriangleSet> shapes;
Texture *t=nullptr;
int windowid;

string getAbsolutePathForFilename(const char * programPath, const char * filename)
{
    string result(programPath);
    if (result.find("\\") == string::npos)
        replace( result.begin(), result.end(), '/', '\\');
    size_t index = result.rfind("src\\bin\\Debug\\");
    if (index != string::npos)
        result = result.substr(0, index);
    else
    {
        index = result.rfind("src\\bin\\Release\\");
        if (index != string::npos)
            result = result.substr(0, index);
        else
        {
            index = result.rfind("\\");
            if (index != string::npos)
                result = result.substr(0, index);
        }
    }
    if (result[result.length() - 1] != '\\')
        result += '\\';

    return result + filename;
}

void initRenderer(const char * programPath, int _windowid)
{
    Texture::init();
    cout << "Loading textures..." << endl;
    t = new Texture(getAbsolutePathForFilename(programPath, "data\\models\\grass-texture.jpg"));
    t->storeOpenGLTextureName(_windowid);
    windowid = _windowid;
    string filename = getAbsolutePathForFilename(programPath, "data\\models\\top_assy.uavsim");
    bool cacheUsed = fileExists(filename);
    if (!cacheUsed)
        filename = getAbsolutePathForFilename(programPath, "data\\models\\top_assy.wrl");
    CompositeFileImporter importer;
    cout << "Loading 3D models..." << endl;
    cout << "Loading: " << filename << endl;
    GroupNode * group = importer.load(filename);
    if (group == NULL)
        cout << "Unable to load from 3D file: " << filename << endl;
    else
    {
        if (!cacheUsed)
        {
            UAVSimBinaryFileExporter saver;
            filename = getAbsolutePathForFilename(programPath, "data\\models\\top_assy.uavsim");
            saver.save(*group, filename);
        }
        vector<Triangle> triangles = group->getTriangles();
        delete group;

        for (auto t = triangles.begin(); t != triangles.end(); t++)
        {
            for (int vertexIndex = 0; vertexIndex < 3; vertexIndex++)
            {
                t->vertices[vertexIndex] = t->vertices[vertexIndex] * 10;
                // translate so the axis of helicopter blade rotation is roughly on (0,0,0).
                t->vertices[vertexIndex].x -= 0.599532;
                t->vertices[vertexIndex].z -= 0.350633;
            }
            t->updateNormal();
        }
        // white part.
        shapes.push_back(ColouredTriangleSet(1, 1, 1));
        shapes.push_back(ColouredTriangleSet(1, 1, 1));
        shapes.push_back(ColouredTriangleSet(1, 1, 1));

        const double whiteMaxY = 3.26;
        const double blade1MaxY = 3.4;
        for (auto t = triangles.begin(); t != triangles.end(); t++)
        {
            double maxY = -99999;
            for (unsigned int vIndex = 0; vIndex < 3; vIndex++)
            {
                maxY = max(maxY, t->vertices[vIndex].y);
            }
            if (maxY <= whiteMaxY)
                shapes[0].triangles.push_back(*t); // white
            else if (maxY <= blade1MaxY)
                shapes[1].triangles.push_back(*t);
            else
                shapes[2].triangles.push_back(*t);
        }
    }
}

void drawGround(double elevation)
{
  const double left = -8;
  const double top = -8;
  const double width = -left * 2;
  const double height = -top * 2;

    glDisable(GL_LIGHT0);
    glDisable(GL_NORMALIZE);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, t->getOpenGLTextureName(windowid));

    glColor3d(1, 1, 1);
    glPushMatrix();
        glRotated(-90, 1,0,0);
        glTranslated(0,0,elevation);
        glBegin(GL_QUADS);
            glTexCoord2d(0,0);
            glVertex2d(left,top);
            glTexCoord2d(1,0);
            glVertex2d(left+width,top);
            glTexCoord2d(1,1);
            glVertex2d(left+width,top+height);
            glTexCoord2d(0,1);
            glVertex2d(left,top+height);
        glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
}

void drawHorizonAndSky()
{
    glClearColor(0.3, 0.5, 1,0.0);
}

void render()
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawHorizonAndSky();

    glClear(GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

        glTranslated(0,-1.3,-2.5);
        glRotated(a * 0.04,0,1,0);
        drawGround(-2 + 1.8 * sin(t * 2));
        shapes[0].draw();
        glPushMatrix();
            glRotated(a * 5, 0, 1, 0);
            shapes[1].draw();
        glPopMatrix();
        glPushMatrix();
            glRotated(-a * 5, 0, 1, 0);
            shapes[2].draw();
        glPopMatrix();
    glPopMatrix();
}
