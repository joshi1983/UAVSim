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
#include <cmath>
#include "io/model_importers/CompositeFileImporter.hpp"
#include "io/model_exporters/UAVSimBinaryFileExporter.hpp"
#include "models/Triangle.hpp"
#include "models/ColouredTriangleSet.hpp"
#include "models/Texture.hpp"
#include "io/Files.hpp"
#include "models/Sky.hpp"
using namespace std;

vector<ColouredTriangleSet> shapes;
Texture *t=nullptr;
int windowid;
double yOffset = -1.3;
Sky *sky;

void verticalShift(double dy)
{
    yOffset += dy;
}

void initRenderer(const char * programPath, int _windowid)
{
    setProgramPath(programPath);
    Texture::init();
    cout << "Loading textures..." << endl;
    t = new Texture("data\\models\\grass-texture.jpg");
    t->storeOpenGLTextureName(_windowid);
    windowid = _windowid;
    string filename = getAbsolutePathForFilename("data\\models\\top_assy.uavsim");
    bool cacheUsed = fileExists(filename);
    if (!cacheUsed)
        filename = getAbsolutePathForFilename("data\\models\\top_assy.wrl");
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
        sky = new Sky();
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
        const double blade1MaxY = 3.412;
        const double blade1AverageY = 3.412;
        for (auto t = triangles.begin(); t != triangles.end(); t++)
        {
            double maxY = -99999;
            double minY = 999999;
            double totalX = 0, totalY = 0, totalZ = 0;
            for (unsigned int vIndex = 0; vIndex < 3; vIndex++)
            {
                maxY = max(maxY, t->vertices[vIndex].y);
                minY = min(minY, t->vertices[vIndex].y);
                totalX += t->vertices[vIndex].x;
                totalY += t->vertices[vIndex].y;
                totalZ += t->vertices[vIndex].z;
            }
            double averageY = (maxY + minY) * 0.5;
            if (averageY <= whiteMaxY)
                shapes[0].triangles.push_back(*t); // main body.
            else if (abs(averageY - blade1AverageY) < 0.015)
            {
                if (abs(totalX) < abs(totalZ))
                    shapes[1].triangles.push_back(*t); // lower propeller
                else
                    shapes[2].triangles.push_back(*t); // upper propeller
            }
            else if (averageY <= blade1MaxY)
                shapes[1].triangles.push_back(*t); // lower propeller
            else
                shapes[2].triangles.push_back(*t); // upper propeller
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
        glTranslated(0,0,elevation + yOffset);
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
    sky->draw(windowid);

    glClear(GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

        glTranslated(0,yOffset,-2.5);
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
