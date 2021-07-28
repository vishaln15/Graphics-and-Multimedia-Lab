#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>

void myInit() {
	glClearColor(2.0, 1.0, 2.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(10);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

void checker() {
	glClear(GL_COLOR_BUFFER_BIT);
	
	int i, j;
	for (i = 0; i < 800; i += 100) {
		for (j = 0; j < 800; j += 50) {
			if (j % 100 == 0) {
				glBegin(GL_QUADS);
				glVertex2d(i, j);
				glVertex2d(i, j + 50);
				glVertex2d(i + 50, j + 50);
				glVertex2d(i + 50, j);
				glEnd();
			}
			else {
				glBegin(GL_QUADS);
				glVertex2d(i + 50, j);
				glVertex2d(i + 50, j + 50);
				glVertex2d(i + 100, j + 50);
				glVertex2d(i + 100, j);
				glEnd();
			}
		}
	}
	glFlush();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Checker Pattern");
	glutDisplayFunc(checker);
	myInit();
	glutMainLoop();
	return 1;
}