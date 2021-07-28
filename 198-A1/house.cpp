#include <GL/glut.h>
#include <GL/gl.h>

void myInit() {
	glClearColor(2.0, 1.0, 2.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(10);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void house() {
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glColor3f(0.5, 0.0, 0.0);
	glVertex2d(200, 400);
	glVertex2d(150, 300);
	glVertex2d(250, 300);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 0.5);
	glVertex2d(150, 300);
	glVertex2d(250, 300);
	glVertex2d(250, 200);
	glVertex2d(150, 200);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2d(200, 400);
	glVertex2d(400, 400);
	glVertex2d(450, 300);
	glVertex2d(250, 300);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2d(250, 300);
	glVertex2d(450, 300);
	glVertex2d(450, 200);
	glVertex2d(250, 200);
	glEnd();
	glFlush();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutCreateWindow("House");
	glutDisplayFunc(house);
	myInit();
	glutMainLoop();
	return 1;
}