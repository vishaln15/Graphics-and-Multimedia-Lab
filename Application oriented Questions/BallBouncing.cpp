#pragma warning(disable: 4996)
#include <iostream>
#include <vector>
#include <gl/glut.h>

int inc = 1;
const int FPS = 5;

void myInit() {
	glClearColor(1, 1, 1, 1);
	glShadeModel(GL_SMOOTH);
	GLfloat diffusion_params[] = {1, 1, 1, 1};
	GLfloat position_params[] = { 0, 0, 1, 0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffusion_params);
	glLightfv(GL_LIGHT0, GL_POSITION, position_params);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void renderScene(int state) {
	if (state == 5)
		inc = -1;
	if (state == 0)
		inc = 1;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gluPerspective(75, 1, 0.1, 20);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 7, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);

	//Ball

	glPushMatrix();
	GLfloat ball_color[] = {0, 0, 0};
	GLfloat ball_shine_factor[] = { 10 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ball_color);
	glMaterialfv(GL_FRONT, GL_SHININESS, ball_shine_factor);
	glTranslatef(0, state, 0);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();

	glutSwapBuffers();
	glutTimerFunc(1000 / FPS, renderScene, state + inc);
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
}

void dummy() {
	glutTimerFunc(1000 / FPS, renderScene, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("Ball Bouncing");
	myInit();
	glutReshapeFunc(reshape);
	glutDisplayFunc(dummy);
	glutMainLoop();
	return 1;
}