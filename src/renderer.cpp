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
#include "models/Triangle.hpp"
#include "models/Texture.hpp"
#include "io/Files.hpp"
#include "deployment/deploymentHelper.hpp"
#include "models/Sky.hpp"
#include "models/Ground.hpp"
#include "models/animation/DefaultAnimation.hpp"
#include "io/animation_importers/CSVAnimationImporter.hpp"
#include "io/screenshots/screenshots.hpp"
#include "AnimationProcessor.hpp"
#include "models/UAV.hpp"
#include "io/config/Config.hpp"
using namespace std;

UAV * uav = nullptr;
int windowid;
int renderCallCount = 0;
double yOffset = -2.1;
bool isShowingGround = true;
bool isShowingSky = true;
Sky *sky;
Animation *animation;
AnimationProcessor *animationProcessor = nullptr;
Ground *ground = nullptr;

void verticalShift(double dy)
{
    yOffset += dy;
}

void initRenderer(const char * programPath, int _windowid)
{
    setProgramPath(programPath);
    UAVSimConfig::config.load();
    initDirectories();
    Texture::init();
    Ground::init(_windowid);
    ground = new Ground();
    updateResolutionFromConfig();
    CSVAnimationImporter csvAnimationImporter;
    animation = csvAnimationImporter.load();
    if (animation != nullptr)
        animationProcessor = new AnimationProcessor(animation, animationState);
    else
        animation = new DefaultAnimation();
    windowid = _windowid;
    isShowingGround = UAVSimConfig::config.getDefaultedBool("/showGround", true);
    isShowingSky = UAVSimConfig::config.getDefaultedBool("/showSky", true);
    cout << "Loading sky model..." << endl;
    sky = new Sky();
    cout << "Loading UAV model..." << endl;
    uav = new UAV();
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
    glPushMatrix();
        glRotated(animationState.cameraPitch, 1, 0, 0);
        drawHorizonAndSky();
        if (isShowingSky)
            sky->draw(windowid, animationState.yaw, 0);

        if (isShowingGround)
        {
            ground->draw(windowid, animationState, yOffset);
        }
        uav->draw(animationState, yOffset);
    glPopMatrix();
}
