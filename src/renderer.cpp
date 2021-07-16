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
#include "models/animation/AnimationProcessor.hpp"
#include "models/UAV.hpp"
#include "io/config/UAVSimConfig.hpp"
#include "io/networking/HTTPServer.hpp"
#include "models/animation/ffmpeg.hpp"
#include "io/networking/browserLauncher.hpp"
using namespace std;

UAV * uav = nullptr;
int windowid;
int renderCallCount = 0;
double yOffset = -0.11;
bool isShowingGround = true;
bool isShowingSky = true;
Sky *sky;
Animation *animation;
AnimationProcessor *animationProcessor = nullptr;
Ground *ground = nullptr;
bool isSavingFrames;

void verticalShift(double dy)
{
    yOffset += dy;
}

void initRenderer(const char * programPath, int _windowid)
{
    setProgramPath(programPath);
    UAVSimConfig::config.load();
    isSavingFrames = UAVSimConfig::config.getDefaultedBool("/csv/isSavingFrames", true);
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
    {
        animation = new DefaultAnimation();
        DefaultAnimation* defaultAnimation = dynamic_cast<DefaultAnimation*>(animation);
        startHttpServer(getAbsolutePathForFilename("data/htdocs"), *defaultAnimation);
        if (UAVSimConfig::config.getDefaultedBool("/httpServer/launchBrowser", true))
            launchRelativeDocument("/");
    }

    windowid = _windowid;
    isShowingGround = UAVSimConfig::config.getDefaultedBool("/showGround", true);
    isShowingSky = UAVSimConfig::config.getDefaultedBool("/showSky", true);
    cout << "Loading sky model..." << endl;
    sky = new Sky();
    cout << "Loading UAV model..." << endl;
    uav = new UAV();
}

void updateFrustrum(const AnimationState & animationState)
{
    UAVModel* model = UAVModel::getInstance();
    double farZ = max(150.0, abs(animationState.cameraZ) + model->getBoundingSphereRadius());
    double nearZ = max(0.02, abs(animationState.cameraZ) - model->getBoundingSphereRadius());
    updateFrustrum(animationState, nearZ, farZ);
}

void updateFrustrum(const AnimationState & animationState, double nearZ, double farZ)
{
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double zoomScale = nearZ * animationState.cameraScale;
    glFrustum(-ar * zoomScale, ar * zoomScale, -zoomScale, zoomScale, nearZ, farZ);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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
    static bool isVideoGenerated = false;

    if (_canSaveScreenshot && isSavingFrames && isSavingScreenshots && isFrameProcessed)
    {
        if (animationProcessor->isWithinAnimation())
        {
            string filename = animationProcessor->getFileName();
            saveScreenshot(filename.c_str());
            if (animationProcessor->isSwitchingMotionBlurGroup())
                switchedMotionBlurGroup(animationProcessor->getBlurGroupFileName());
        }
        else if ((!isVideoGenerated) && isFFMPEGAvailable())
        {
            cout << "About to create video. isVideoGenerated = " << isVideoGenerated << endl;
            isVideoGenerated = true;
            animationProcessor->deleteFrameAfterAnimation();
            createVideoFile();
        }
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
    {
        const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
        animation->getState(t, animationState);
    }

    updateFrustrum(animationState);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        if (animationState.activeCamera == nullptr)
            glRotated(animationState.cameraPitch, 1, 0, 0);
        else
        {
            Vector3D &axis = animationState.activeCamera->rotationAxis;
            glRotated(animationState.activeCamera->rotationAngle, axis.x, axis.y, axis.z);
        }

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
