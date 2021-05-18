#include "Sky.hpp"
#include "../io/Files.hpp"

double d=0;

Sky::Sky(): texture("data\\models\\skybox_texture3.jpg")
{
}

void Sky::draw(int windowid, double cameraYaw, double cameraPitch)
{
    const double D = 4;
    const double third = 1.0 / 3;
    const double quarter = 1.0 / 4;
    d += 0.3;

    texture.storeOpenGLTextureName(windowid);
    glDisable(GL_LIGHT0);
    glDisable(GL_NORMALIZE);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);
    glEnable( GL_TEXTURE_2D );
    glDisable(GL_DEPTH_TEST);

    glBindTexture( GL_TEXTURE_2D, texture.getOpenGLTextureName(windowid));
    glColor3d(1, 1, 1);
    glPushMatrix();
        glRotated(180, 1, 0, 0);
        glTranslated(0,0,-2);
        glRotated(cameraYaw, 0, 1, 0);
        glRotated(cameraPitch, 1, 0, 0);

        /*
        Taken from:
        https://www.youtube.com/watch?v=DlOT8MJ7mrc
        */
        // right
        glBegin(GL_QUADS);
            glTexCoord2f(0,third); glVertex3f(-D,-D,-D);
            glTexCoord2f(quarter,third); glVertex3f(+D,-D,-D);
            glTexCoord2f(quarter,2*third); glVertex3f(+D,+D,-D);
            glTexCoord2f(0,2*third); glVertex3f(-D,+D,-D);
        glEnd();
        // front
        glBegin(GL_QUADS);
            glTexCoord2f(quarter,third); glVertex3f(+D,-D,-D);
            glTexCoord2f(2*quarter,third); glVertex3f(+D,-D,+D);
            glTexCoord2f(2*quarter,2*third); glVertex3f(+D,+D,+D);
            glTexCoord2f(quarter,2*third); glVertex3f(+D,+D,-D);
        glEnd();
        // left
        glBegin(GL_QUADS);
            glTexCoord2f(2*quarter,third); glVertex3f(+D,-D,+D);
            glTexCoord2f(3*quarter,third); glVertex3f(-D,-D,+D);
            glTexCoord2f(3*quarter,2*third); glVertex3f(-D,+D,+D);
            glTexCoord2f(2*quarter,2*third); glVertex3f(+D,+D,+D);
        glEnd();
        // back
        glBegin(GL_QUADS);
            glTexCoord2f(3*quarter,third); glVertex3f(-D,-D,+D);
            glTexCoord2f(1,third); glVertex3f(-D,-D,-D);
            glTexCoord2f(1,2*third); glVertex3f(-D,+D,-D);
            glTexCoord2f(3*quarter,2*third); glVertex3f(-D,+D,+D);
        glEnd();
        // bottom
        glBegin(GL_QUADS);
            glTexCoord2f(quarter,1); glVertex3f(-D,+D,-D);
            glTexCoord2f(quarter,2*third); glVertex3f(+D,+D,-D);
            glTexCoord2f(2*quarter,2*third); glVertex3f(+D,+D,+D);
            glTexCoord2f(2*quarter,1); glVertex3f(-D,+D,+D);
        glEnd();

        // top
        glBegin(GL_QUADS);
            glTexCoord2f(quarter,third); glVertex3f(+D,-D,-D);
            glTexCoord2f(quarter,0); glVertex3f(-D,-D,-D);
            glTexCoord2f(2*quarter,0); glVertex3f(-D,-D,+D);
            glTexCoord2f(2*quarter,third); glVertex3f(+D,-D,+D);
        glEnd();

    glPopMatrix();

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
}
