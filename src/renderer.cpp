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
#include "deployment/deploymentHelper.hpp"
#include "models/Sky.hpp"
#include "models/animation/DefaultAnimation.hpp"
#include "io/config/Config.hpp"
#include "lib/rapidjson/pointer.h"
#include "io/animation_importers/CSVAnimationImporter.hpp"
#include "io/screenshots/screenshots.hpp"
#include "AnimationProcessor.hpp"
using namespace std;

vector<ColouredTriangleSet> shapes;
Texture *t=nullptr;
int windowid;
int renderCallCount = 0;
double yOffset = -2.1;
bool isShowingGround = true;
Sky *sky;
Animation *animation;
AnimationProcessor *animationProcessor = nullptr;

void verticalShift(double dy)
{
    yOffset += dy;
}

bool isConfigShowingGround()
{
    UAVSimConfig& c = UAVSimConfig::config;
    string path = string("/showGround");
    rapidjson::Value* a =  rapidjson::Pointer(path.c_str()).Get(c.doc);
    if (a != nullptr)
        return a->GetBool();
    else
        return true;
}

void initRenderer(const char * programPath, int _windowid)
{
    setProgramPath(programPath);
    UAVSimConfig::config.load();
    initDirectories();
    Texture::init();
    updateResolutionFromConfig();
    CSVAnimationImporter csvAnimationImporter;
    animation = csvAnimationImporter.load();
    if (animation != nullptr)
        animationProcessor = new AnimationProcessor(animation, animationState);
    else
        animation = new DefaultAnimation();
    cout << "Loading textures..." << endl;
    t = new Texture("data\\models\\grass-texture.jpg");
    t->storeOpenGLTextureName(_windowid);
    windowid = _windowid;
    string filename = getAbsolutePathForFilename("data\\models\\cache\\top_assy.uavsim");
    bool cacheUsed = fileExists(filename);
    if (!cacheUsed)
        filename = getAbsolutePathForFilename("data\\models\\top_assy.wrl");
    CompositeFileImporter importer;
    isShowingGround = isConfigShowingGround();
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
            filename = getAbsolutePathForFilename(programPath, "data\\models\\cache\\top_assy.uavsim");
            saver.save(*group, filename);
        }
        sky = new Sky();
        vector<Triangle> triangles = group->getTriangles();
        delete group;
        double minY = 999999;

        for (auto t = triangles.begin(); t != triangles.end(); t++)
        {
            for (int vertexIndex = 0; vertexIndex < 3; vertexIndex++)
            {
                t->vertices[vertexIndex] = t->vertices[vertexIndex] * 10;
                // translate so the axis of helicopter blade rotation is roughly on (0,0,0).
                t->vertices[vertexIndex].x -= 0.599532;
                t->vertices[vertexIndex].y += 0.0935;
                t->vertices[vertexIndex].z -= 0.350633;
                minY = min(minY, t->vertices[vertexIndex].y);
            }
            t->updateNormal();
        }
        // white part.
        shapes.push_back(ColouredTriangleSet(1, 1, 1));
        shapes.push_back(ColouredTriangleSet(1, 1, 1));
        shapes.push_back(ColouredTriangleSet(1, 1, 1));

        const double whiteMaxY = 3.2;
        const double blade1MaxY = 3.5;
        const double blade1AverageY = 3.5;
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

void drawGround()
{
  const double left = -4;
  const double top = -4;
  const double width = -left * 2;
  const double height = -top * 2;

    glDisable(GL_LIGHT0);
    glDisable(GL_NORMALIZE);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, t->getOpenGLTextureName(windowid));

    glColor3d(1, 1, 1);
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
    renderCallCount++;
    static bool isFrameProcessed = false;
    bool isSavingScreenshots = (animationProcessor != nullptr && renderCallCount > 100);
    bool _canSaveScreenshot = canSaveScreenshot();
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;

    if (_canSaveScreenshot && isSavingScreenshots && animationProcessor->isWithinAnimation() && isFrameProcessed)
    {
        string filename = animationProcessor->getFileName();
        saveScreenshot(filename.c_str());
    }

    if (isSavingScreenshots)
    {
        if (_canSaveScreenshot)
        {
            animationProcessor->processNextFrame();
            isFrameProcessed = true;
        }
    }
    else
        animation->getState(t, animationState);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawHorizonAndSky();
    sky->draw(windowid, animationState.yaw, 10);

    glClear(GL_DEPTH_BUFFER_BIT);
    if (isShowingGround)
    {
        glPushMatrix();
            //glRotated(animationState.yaw,0,1,0);
            glRotated(-90, 1, 0, 0);
            glTranslated(animationState.x, animationState.z, animationState.y + yOffset);
            glRotated(-animationState.yaw, 0, 0, 1);
            drawGround();
        glPopMatrix();
    }
    glPushMatrix();
        glTranslated(0,yOffset,-3.0);
        glRotated(10, 1, 0, 0);
        glRotated(10, 0, 1, 0);
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
