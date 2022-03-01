#pragma warning (disable: 4996)

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <gl/glut.h>
#include <vector>

#define HEIGHT 250
#define WIDTH -250

using namespace std;

typedef struct window {
	double xmin, xmax, ymin, ymax;
};

window w;

vector<double> TBRL1(4, 0);
vector<double> TBRL2(4, 0);
double x1, y_1, x2, y2;

void myInit() {
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glColor3f(0, 0, 0);
	glPointSize(1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(WIDTH, HEIGHT, WIDTH, HEIGHT);
}

void drawAxis() {
	glBegin(GL_LINES);
	glVertex2d(WIDTH, 0);
	glVertex2d(HEIGHT, 0);
	glVertex2d(0, WIDTH);
	glVertex2d(0, HEIGHT);
	glEnd();
}

void drawBoundary(window w) {
	glBegin(GL_LINE_LOOP);
	glVertex2d(w.xmin, w.ymin);
	glVertex2d(w.xmin, w.ymax);
	glVertex2d(w.xmax, w.ymax);
	glVertex2d(w.xmax, w.ymin);
	glEnd();
}

void drawLine(double x1, double y_1, double x2, double y2) {
	glBegin(GL_LINES);
	glVertex2d(x1, y_1);
	glVertex2d(x2, y2);
	glEnd();
}

void getRegionCode(window w, int point, double x, double y) {
	if (point == 1)
	{	
		if (y > w.ymax) TBRL1[0] = 1;
		if (y < w.ymin) TBRL1[1] = 1;
		if (x > w.xmax) TBRL1[2] = 1;
		if (x < w.xmin) TBRL1[3] = 1;
	}
	
	else
	{
		if (y > w.ymax) TBRL2[0] = 1;
		if (y < w.ymin) TBRL2[1] = 1;
		if (x > w.xmax) TBRL2[2] = 1;
		if (x < w.xmin) TBRL2[3] = 1;
	}
}

bool accept() {
	for (int i = 0; i < TBRL1.size(); i++)
	{
		if (TBRL1[i] || TBRL2[i])
			return false;
	}
	return true;
}

bool reject() {
	for (int i = 0; i < TBRL1.size(); i++)
	{
		if (TBRL1[i] && TBRL2[i])
			return true;
	}
	return false;
}

void lineClippingDemo() {
	glClear(GL_COLOR_BUFFER_BIT);
	drawAxis();
	window w;
	cout << "--------COHEN SUTHERLAND LINE CLIPPING ALGORITHM WRT RIGHT EDGE--------\n\nEnter the window coordinates xmin, xmax, ymin, ymax: ";
	cin >> w.xmin >> w.xmax >> w.ymin >> w.ymax;
	cout << "\nThe window coordinates are : " << w.xmin << " " << w.xmax << " " << w.ymin << " " << w.ymax;

	drawBoundary(w);
	cout << "\nEnter the line coordinates: ";
	cin >> x1 >> y_1 >> x2 >> y2;
	cout << "\nThe line coordinates are : " << x1 << " " << y_1 << " " << x2 << " " << y2;
	cout << "\nCLIPPING...\n\n";
	getRegionCode(w, 1, x1, y_1);
	getRegionCode(w, 2, x2, y2);
	glColor3f(1, 0, 0);
	drawLine(x1, y_1, x2, y2);
	if (accept())
	{
		cout << "Trivial Accept!\n";
		glFlush();
		return;
	}

	if (reject()) {
		cout << "Trivial Reject!\n";
		glFlush();
		return;
	}
	cout << "1 Point intersection wrt right edge\n";
	double m = (y2 - y_1) / (x2 - x1);
	double y_inter = m * (w.xmax - x1) + y_1;
	glColor3f(0, 0, 1);
	drawLine(x1, y_1, w.xmax, y_inter);
	cout << "\nClipping Completed!\n\n\n";
	glFlush();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(HEIGHT, HEIGHT);
	glutCreateWindow("Cohen Sutherland Line Clipping Algorithm");
	myInit();
	glutDisplayFunc(lineClippingDemo);
	glutMainLoop();
	return 1;
}