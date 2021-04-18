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
#include "io/model_importers/X3DFileImporter.hpp"
#include "models/Triangle.hpp"

using namespace std;

vector<Triangle> triangles;

void initRenderer()
{
    const char * filename = "C:\\learning\\UAVSim\\data\\models\\top_assembly.x3d";
    X3DFileImporter importer;
    cout << "Loading 3D models..." << endl;
    GroupNode * group = importer.load(filename);
    triangles = group->getTriangles();
    cout << "Loaded.  Triangle count = " << triangles.size() << endl;
    for (auto t = triangles.begin(); t != triangles.end(); t++)
    {
        t->updateNormal();
    }
}

void drawHorizonAndSky()
{

}

void render()
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;
    const double scale = 10;
    drawHorizonAndSky();

    glColor3f(1, 1, 1);
    glPushMatrix();

        glTranslated(0,-1.3,-2.5);
        glRotated(a,0,1,0);

        glBegin(GL_TRIANGLES);
        for (auto it = triangles.begin(); it != triangles.end(); it++)
        {
            Vertex &normal = it->cachedNormal;
            glNormal3f(normal.x, normal.y, normal.z);
            for (int i = 0; i < 3; i++)
            {
                Vertex &v = it->vertices[i];
                glVertex3f(v.x * scale, v.y * scale, v.z * scale);
            }
        }
        glEnd();
    glPopMatrix();
}
