#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<cmath>

int xRotate = 0, yRotate = 0, ytranslate = 0, xTranslate = 0;

void initialize() {
	glClearColor(1, 1, 1, 0);
	glColor3f(0, 0, 0);
	glPointSize(3);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void draw_axes() {
	glBegin(GL_LINES);
	glVertex2f(-2, 0);
	glVertex2f(2, 0);
	glVertex2f(0, -2);
	glVertex2f(0, 2);
	glEnd();
	glFlush();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glOrtho(-2, 2, -2, 2, -2, 2);
	gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);
	glRotatef(10, 1, 0, 0);
	glRotatef(yRotate, 0, 1, 0);
	glTranslatef(xTranslate, 0, 0);
	//glScalef(0.5, 0, 0);
	glColor3f(1, 0, 0);
	glutWireCube(0.5);
	glPopMatrix();
	glutSwapBuffers();

}

void reshape(int width, int height) {
	glViewport(0, 0, width, height); // Set our viewport to the size of our window  
}


void update(int value) {
	xRotate += 0.5;
	xTranslate += 1;
	yRotate += 1;
	if (xRotate > 2) {
		xRotate -= 2;
	}
	if (xTranslate >= 2) {
		xTranslate -= 1;
	}
	if (yRotate > 360) {
		yRotate -= 360;
	}
	glutPostRedisplay(); // Inform GLUT that the display has changed
	glutTimerFunc(5, update, 0);//Call update after each 25 millisecond
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("3d transforms");
	glEnable(GL_DEPTH_TEST);
	initialize();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(25, update, 0);
	glutMainLoop();
	return 0;
}