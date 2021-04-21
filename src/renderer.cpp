#include "renderer.hpp"
#define GL_GLEXT_PROTOTYPES
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include "io/model_importers/CompositeFileImporter.hpp"
#include "models/Triangle.hpp"

using namespace std;

vector<Triangle> triangles;

void initRenderer()
{
    const char * filename = "C:\\learning\\UAVSim\\data\\models\\top_assy.wrl";
    CompositeFileImporter importer;
    cout << "Loading 3D models..." << endl;
    cout << "Loading: " << filename << endl;
    GroupNode * group = importer.load(filename);
    if (group == NULL)
        cout << "Unable to load from 3D file: " << filename << endl;
    else
    {
        triangles = group->getTriangles();
        delete group;

        for (auto t = triangles.begin(); t != triangles.end(); t++)
        {
            for (int vertexIndex = 0; vertexIndex < 3; vertexIndex++)
            {
                t->vertices[vertexIndex] = t->vertices[vertexIndex] * 10;
                // translate so the axis of helicopter blade rotation is roughly on (0,0,0).
                t->vertices[vertexIndex].x -= 0.6;
                t->vertices[vertexIndex].z -= 0.4;
            }
            t->updateNormal();
        }
    }
}

void drawGround()
{
  const double left = -8;
  const double top = -8;
  const double width = -left * 2;
  const double height = -top * 2;

    glColor3d(0,2.0,0);
    glPushMatrix();
        glRotated(-90, 1,0,0);
        glTranslated(0,3,0);
        glBegin(GL_QUADS);
            glVertex2d(left,top);
            glVertex2d(left+width,top);
            glVertex2d(left+width,top+height);
            glVertex2d(left,top+height);
        glEnd();
    glPopMatrix();
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
        glRotated(a,0,1,0);
        drawGround();
        glColor3f(1, 1, 1);
        glBegin(GL_TRIANGLES);
        for (auto it = triangles.begin(); it != triangles.end(); it++)
        {
            Vertex &normal = it->cachedNormal;
            glNormal3f(normal.x, normal.y, normal.z);
            for (int i = 0; i < 3; i++)
            {
                Vertex &v = it->vertices[i];
                glVertex3f(v.x, v.y, v.z);
            }
        }
        glEnd();

    glPopMatrix();
}
