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
  const double left = -10;
  const double top = 0;
  const double width = -left * 2;
  const double height = 10 * 2;

    glDisable(GL_LIGHT0);
    glDisable(GL_NORMALIZE);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    glEnable( GL_TEXTURE_2D );
    glDisable(GL_DEPTH_TEST);

    glColor3d(1, 1, 1);
    for (double scale = 0.005; scale < 5; scale *= 4)
    {
        glPushMatrix();

            glRotated(-90, 1, 0, 0);
            glTranslated(animationState.x * scale, animationState.z * scale, (yOffset - animationState.y) * scale);
            glTranslated(0, -animationState.cameraZ * scale, -animationState.cameraY * scale);
            glRotated(-animationState.yaw, 0, 0, 1);
            glTranslated(0, animationState.cameraZ * scale, animationState.cameraY * scale);
            glBindTexture( GL_TEXTURE_2D, grass->getOpenGLTextureName(windowid));
            double textureScale = 1.0 / scale;
            glBegin(GL_QUADS);
                glTexCoord2d(0,0);
                glVertex2d(left,top);
                glTexCoord2d(textureScale,0);
                glVertex2d(left+width,top);
                glTexCoord2d(textureScale,textureScale);
                glVertex2d(left+width,top+height);
                glTexCoord2d(0,textureScale);
                glVertex2d(left,top+height);
            glEnd();

            double top2 = top - height;
            glBindTexture( GL_TEXTURE_2D, water->getOpenGLTextureName(windowid));
            glBegin(GL_QUADS);
                glTexCoord2d(0,0);
                glVertex2d(left,top2);
                glTexCoord2d(textureScale,0);
                glVertex2d(left+width,top2);
                glTexCoord2d(textureScale,textureScale);
                glVertex2d(left+width,top);
                glTexCoord2d(0,textureScale);
                glVertex2d(left,top);
            glEnd();

        glPopMatrix();
    }

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
}
