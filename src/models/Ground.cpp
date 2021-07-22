#include "Ground.hpp"
#include "Texture.hpp"
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
using namespace std;

Texture *grass=nullptr;
Texture *water=nullptr;

void Ground::init(int windowid)
{
    cerr << "About to load texture." << endl;
    grass = new Texture("data\\models\\grass-texture.jpg");
    grass->storeOpenGLTextureName(windowid);
    water = new Texture("data\\models\\water.jpg");
    water->storeOpenGLTextureName(windowid);
}

void Ground::draw(int windowid, const AnimationState & animationState, double yOffset) const
{
  const double left = -150;
  const double top = 0;
  const double width = -left * 2;
  const double height = 150 * 2;
  const double beachWidth = height * 0.005;
  const double beachHeight = 0.2;

    glDisable(GL_LIGHT0);
    glDisable(GL_NORMALIZE);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    glEnable( GL_TEXTURE_2D );

    glColor3d(1, 1, 1);
    glPushMatrix();

        glRotated(-animationState.cameraYaw, 0, 1, 0);
		glTranslated(0, 0, animationState.cameraZ);
        glRotated(animationState.cameraYaw, 0, 1, 0);

        glRotated(-animationState.yaw, 0, 1, 0);

        glTranslated(animationState.x, (yOffset - animationState.y) + animationState.cameraY, animationState.z);

        glBindTexture( GL_TEXTURE_2D, grass->getOpenGLTextureName(windowid));
        double textureScale = 50.0;
        glBegin(GL_QUADS);
            glTexCoord2d(0,0);
            glVertex3d(left+width, 0, top);
            glTexCoord2d(textureScale,0);
            glVertex3d(left, 0, top);
            glTexCoord2d(textureScale,textureScale);
            glVertex3d(left, 0, top+height);
            glTexCoord2d(0,textureScale);
            glVertex3d(left+width, 0, top+height);
        glEnd();

        double top1 = top - height - beachWidth;
        glBindTexture( GL_TEXTURE_2D, water->getOpenGLTextureName(windowid));
        double waterAnimationOffset = cos(animationState.waterAnimationT);
        double waveHeight = (waterAnimationOffset + 1) * 0.05;
        double waveWidth = waveHeight * beachWidth / beachHeight;
        glPushMatrix();
            glTranslated(0, -beachHeight, 0);
            glBegin(GL_QUADS);
                glTexCoord2d(0,0);
                glVertex3d(left+width, 0, top1);
                glTexCoord2d(textureScale,0);
                glVertex3d(left, 0, top1);
                glTexCoord2d(textureScale,textureScale);
                glVertex3d(left, waveHeight, -beachWidth + waveWidth);
                glTexCoord2d(0,textureScale);
                glVertex3d(left+width, waveHeight, -beachWidth + waveWidth);
            glEnd();
        glPopMatrix();

        // Draw beach.
        glDisable(GL_TEXTURE_2D);
        glColor3d(1, 0.8, 0.5);
        glBegin(GL_QUADS);
            glVertex3d(left+width, -beachHeight, -beachWidth);
            glVertex3d(left, -beachHeight, -beachWidth);
            glVertex3d(left,0, 0);
            glVertex3d(left+width,0, 0);
        glEnd();

    glPopMatrix();

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
}
