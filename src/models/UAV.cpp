#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <string>
#include <iostream>
#include "UAV.hpp"
using namespace std;

void UAV::draw(const AnimationState & animationState, double yOffset) const
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		glTranslated(0, animationState.cameraY + yOffset, animationState.cameraZ);
        glRotated(-animationState.pitch, 0, 0, 1);
        glRotated(-animationState.roll, 1, 0, 0);
		model.shapes[0].draw();
		glPushMatrix();
            glTranslated(0, model.servoPivotY, 0);
            glRotated(animationState.steerAngle2 * 0.5, 1, 0, 0);
            glTranslated(0, -model.servoPivotY, 0);
            for (int i = 4; i < 6; i++)
                model.shapes[i].draw();
		glPopMatrix();
		glPushMatrix();
            glTranslated(0, model.servoPivotY, 0);
            glRotated(animationState.steerAngle1 * 0.5, 0, 0, 1);
            glTranslated(0, -model.servoPivotY, 0);
            for (int i = 6; i < 8; i++)
                model.shapes[i].draw();
		glPopMatrix();
		glPushMatrix();
            glTranslated(model.steeringPivot.x, model.steeringPivot.y, model.steeringPivot.z);
            glRotated(animationState.steerAngle1, 0, 0, 1);
            glRotated(animationState.steerAngle2, 1, 0, 0);
            glTranslated(-model.steeringPivot.x, -model.steeringPivot.y, -model.steeringPivot.z);
            model.shapes[3].draw();
            glPushMatrix();
                glRotated(animationState.bladeAngle, 0, 1, 0);
                model.shapes[1].draw();
            glPopMatrix();
            glPushMatrix();
                glRotated(-animationState.bladeAngle, 0, 1, 0);
                model.shapes[2].draw();
            glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}
