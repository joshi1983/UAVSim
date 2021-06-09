#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "ColouredTriangleSet.hpp"

using namespace std;

ColouredTriangleSet::ColouredTriangleSet(double r, double g, double b): r(r), g(g), b(b)
{

}

void ColouredTriangleSet::draw() const
{
	glColor3f(r, g, b);
	glBegin(GL_TRIANGLES);
	for (auto it = triangles.begin(); it != triangles.end(); it++)
	{
		const Vector3D &normal = it->cachedNormal;
		glNormal3f(normal.x, normal.y, normal.z);
		for (int i = 0; i < 3; i++)
		{
			const Vertex &v = it->vertices[i];
			glVertex3f(v.p.x, v.p.y, v.p.z);
		}
	}
	glEnd();
}
