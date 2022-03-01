#pragma warning(disable: 4996)
#include <gl/glut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#define VAL 500

using namespace std;

double theta = 0, alpha = 0;
bool flag = false;

void myInit() {
	glClearColor(1, 1, 1, 0);
	glEnable(GL_DEPTH);
}

void keyPress(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'd':
		alpha++;
		break;
	case 'a':
		alpha--;
		break;
	case 'w':
		theta++;
		break;
	case 's':
		theta--;
		break;
	case 32:
		flag = !flag;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (flag)
		glOrtho(-VAL, VAL, -VAL, VAL, -VAL, VAL);
	else
		gluPerspective(100, 1, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 300, 0, 0, 0, 0, 1, 0);
	glRotatef(alpha, 0, 1, 0);
	glRotatef(theta, 1, 0, 0);
	glColor3f(1, 0, 0);
	// glutWireTorus(50, 150, 20, 20);
	glutWireTeapot(100);
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(2 * VAL, 2 * VAL);
	glutCreateWindow("Projection!");
	myInit();
	glutKeyboardFunc(keyPress);
	glutDisplayFunc(display);
	glutMainLoop();
	return 1;
}