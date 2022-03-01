#include<gl/glut.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
using namespace std;

int inc = 1;
const int FPS = 5;

void myinit() {
	glClearColor(0, 0, 0, 1);
	glShadeModel(GL_SMOOTH);
	GLfloat diffusion_params[] = { 1,1,1,1 };
	GLfloat position_params[] = { 0,0,1,0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffusion_params);
	glLightfv(GL_LIGHT0, GL_POSITION, position_params);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void renderScene(int state) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (state == 0)
		inc = 1;
	if (state == 10)
		inc = -1;

	gluPerspective(75, 1, 0.1, 20);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 7, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);

	//SUN
	glPushMatrix();
	GLfloat sun_colour[] = { 1, 0.5, 0.2, 0 };
	GLfloat sun_shine_factor[] = { 10 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, sun_colour);
	glMaterialfv(GL_FRONT, GL_SHININESS, sun_shine_factor);
	glutSolidSphere(1, 20, 20);
	glPopMatrix();

	//Planet 1
	glPushMatrix();
	GLfloat one_colour[] = { 0.6, 0.8, 0.3, 0.2 };
	GLfloat one_shine[] = { 100 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, one_colour);
	glMaterialfv(GL_FRONT, GL_SHININESS, one_shine);
	glRotatef(5 * state, 0, 0, 1);
	glTranslatef(4, 0, 0);
	glutSolidSphere(0.5, 20, 20);
	glPopMatrix();


	/*//Planet 2
	glPushMatrix();
	GLfloat two_colour[] = { 0.5, 0.9, 0.8, 0.9 };
	GLfloat two_shine[] = { 1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, two_colour);
	glMaterialfv(GL_FRONT, GL_SHININESS, two_shine);
	glRotatef(5 * state, 0, 0, 1);
	glTranslatef(-4, 0, 0);
	glutSolidSphere(0.3, 20, 20);
	glPopMatrix();

	//Planet 3
	glPushMatrix();
	GLfloat three_colour[] = { 0, 0.1, 0.9, 0.6 };
	GLfloat three_shine[] = { 20 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, three_colour);
	glMaterialfv(GL_FRONT, GL_SHININESS, three_shine);
	glRotatef(5 * state, 0, 0, 1);
	glTranslatef(0, 4, 0);
	glutSolidSphere(0.6, 20, 20);
	glPopMatrix();


	//Planet 4
	glPushMatrix();
	GLfloat four_colour[] = { 0.7, 0.1, 0.9, 0.6 };
	GLfloat four_shine[] = { 20 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, four_colour);
	glMaterialfv(GL_FRONT, GL_SHININESS, four_shine);
	glRotatef(5 * state, 0, 0, 1);
	glTranslatef(0, -4, 0);
	glutSolidSphere(0.7, 20, 20);
	glPopMatrix();

	//Planet 5
	glPushMatrix();
	GLfloat five_colour[] = { 0.9, 0.9, 0.9, 0.3 };
	GLfloat five_shine[] = { 200 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, five_colour);
	glMaterialfv(GL_FRONT, GL_SHININESS, five_shine);
	glRotatef(5 * state, 0, 0, 1);
	glTranslatef(3, -3, 0);
	glutSolidSphere(0.3, 20, 20);
	glPopMatrix();

	//Planet 6
	glPushMatrix();
	GLfloat six_colour[] = { 0, 0.9, 0.9, 0.3 };
	GLfloat six_shine[] = { 50 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, six_colour);
	glMaterialfv(GL_FRONT, GL_SHININESS, six_shine);
	glRotatef(5 * state, 0, 0, 1);
	glTranslatef(-3, -3, 0);
	glutSolidSphere(0.6, 20, 20);
	glPopMatrix();

	//Planet 7
	glPushMatrix();
	GLfloat sev_colour[] = { 1, 0.1, 0, 0.3 };
	GLfloat sev_shine[] = { 50 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, sev_colour);
	glMaterialfv(GL_FRONT, GL_SHININESS, sev_shine);
	glRotatef(5 * state, 0, 0, 1);
	glTranslatef(-3, 3, 0);
	glutSolidSphere(0.2, 20, 20);
	glPopMatrix();


	//Planet 8
	glPushMatrix();
	GLfloat eight_colour[] = { 0.5, 0.5, 0.5, 0.6 };
	GLfloat eight_shine[] = { 50 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, eight_colour);
	glMaterialfv(GL_FRONT, GL_SHININESS, eight_shine);
	glRotatef(5 * state, 0, 0, 1);
	glTranslatef(3, 3, 0);
	glutSolidSphere(0.4, 20, 20);
	glPopMatrix();
	*/

	glutSwapBuffers();
	glutTimerFunc(1000 / FPS, renderScene, state + inc);

}


/*void reshape(int w, int h) {
	glViewport(0, 0, w, h);
}
*/

void sceneDemo() {
	glutTimerFunc(1000 / FPS, renderScene, 0);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("OwnAnimations");
	glutDisplayFunc(sceneDemo);
	//glutReshapeFunc(reshape);
	myinit();
	glutMainLoop();
	return 1;
}