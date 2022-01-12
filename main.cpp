#include <iostream>
#include <GL/glut.h>

#include "vec3.h"
#include "transform.h"

#define PROJ_ORTHO 0
#define PROJ_PER 1

#define WIDTH 512
#define HEIGHT 512

Transform * root;

void renderTransform(Transform *tform)
{
	glPushMatrix();
	tform->applyGlobalTransformations();

	//scale locally without affecting children
	glPushMatrix();
	tform->applyLocalTransformations();
	GLUquadric *quad = nullptr;
	switch (tform->objectType)
	{
		case OBJ_CYLINDER:
			//orient to point cylinder up, (0, 1, 0)
			//note that we're still transforming locally, since a matrix pop is coming up.
			glRotated(-90, 1, 0, 0);

			quad = gluNewQuadric();
			gluQuadricNormals(quad, GL_TRUE);
			gluCylinder(quad, 0.1, 0.1, 0.5, 32, 1);
			break;
		case OBJ_SPHERE:
			quad = gluNewQuadric();
			gluQuadricNormals(quad, GL_TRUE);
			gluSphere(quad, 0.5, 16, 16);
			break;
		case OBJ_LINE:
		default:
			glBegin(GL_LINES);
			glVertex2d(0, 0);
			glVertex2d(0, 0.5);
			glEnd();
			break;
	}
	glPopMatrix();

	//now, with tform's global transformations only, we render the children.
	for (const auto &pair: tform->children)
	{
		renderTransform(pair.second);
	}

	glPopMatrix();
}

void setProjection(int proj_type)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	switch (proj_type)
	{
		case PROJ_ORTHO:
			glOrtho(-0.1, 0.1, -0.1, 0.1, 0.15, 100);
		case PROJ_PER:
		default:
			glFrustum(-0.1, 0.1, -0.1, 0.1, 0.15, 100);
	}

	glMatrixMode(GL_MODELVIEW);
}

bool toggledOrtho = false;
void toggleOrthoPerspective()
{
	setProjection(toggledOrtho ? PROJ_PER : PROJ_ORTHO);
	toggledOrtho = !toggledOrtho;
}

void render(GLvoid)
{
	if (root == nullptr) return;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderTransform(root);

	glFlush();
	glutSwapBuffers();
}

#include "scenes.h"

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Projection Demo/Experiment");
	glEnable(GL_DEPTH_TEST);

	loadArmScene();

	setProjection(PROJ_PER);

	glutDisplayFunc(render);
	glutMainLoop();

	return 0;
}
