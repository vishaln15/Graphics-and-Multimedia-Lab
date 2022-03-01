#pragma warning (disable: 4996)
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <gl/glut.h>
#include <Windows.h>

using namespace std;

const int FPS = 5;
double sAngle = 0, mAngle = 0, hAngle = 0; // initial angles for sec, min, hour hands

void myInit() {
	glClearColor(1, 1, 1, 0);
	glColor3f(0, 0, 0);
	glPointSize(6);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
}

void draw_pixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void circle(int x_centre, int y_centre, int r) {
	int x = r, y = 0;

	if (r > 0) {
		draw_pixel(x + x_centre, -y + y_centre);
		draw_pixel(y + x_centre, x + y_centre);
		draw_pixel(-y + x_centre, x + y_centre);
	}

	int P = 1 - r;
	while (x > y) {
		y++;

		if (P <= 0)
			P = P + 2 * y + 1;

		else {
			x--;
			P = P + 2 * y - 2 * x + 1;
		}

		draw_pixel(x + x_centre, y + y_centre);
		draw_pixel(-x + x_centre, y + y_centre);
		draw_pixel(x + x_centre, -y + y_centre);
		draw_pixel(-x + x_centre, -y + y_centre);

		if (x != y) {
			draw_pixel(y + x_centre, x + y_centre);
			draw_pixel(-y + x_centre, x + y_centre);
			draw_pixel(y + x_centre, -x + y_centre);
			draw_pixel(-y + x_centre, -x + y_centre);

		}
	}
}

vector<double> multiply(vector<vector<double>> mat1, vector<double> mat2) {
	vector<double> product(3, 0);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			product[i] += mat1[i][j] * mat2[j];
	}
	return product;
}

vector<double> translate(vector<double> P, double tx, double ty) {
	vector<vector<double>> T(3, vector<double>(3, 0));
	vector<double> product;
	for (int i = 0; i < 3; i++)
		T[i][i] = 1;

	T[0][2] = tx;
	T[1][2] = ty;
	product = multiply(T, P);
	return product;
}


vector<double> rotate(vector<double> P, double theta) {
	vector<vector<double>> S(3, vector<double>(3, 0));
	vector<double> product;
	S[0][0] = cos(theta);
	S[0][1] = -sin(theta);
	S[1][0] = sin(theta);
	S[1][1] = cos(theta);
	S[2][2] = 1;
	product = multiply(S, P);
	return product;
}


//Rotates a point/vector of form {x,y,1} with respect to a fixed point (fx,fy) = (250,250) i.e center of the clock

vector<double> rotate(vector<double> P, double theta, double fx, double fy) {
	vector<double> product;
	product = translate(P, -fx, -fy);
	product = rotate(product, theta);
	product = translate(product, fx, fy);
	return product;
}

// Draws the seconds (red) hand of the clock
void sLine(vector<vector<double>> v) {
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex2d(v[0][0], v[0][1]);
	glVertex2d(v[1][0], v[1][1]);
	glEnd();
}

// Draws the mins (green) hand of the clock
void mLine(vector<vector<double>> v) {
	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex2d(v[0][0], v[0][1]);
	glVertex2d(v[1][0], v[1][1]);
	glEnd();
}

// Draws the hours (blue) hand of the clock
void hLine(vector<vector<double>> v) {

	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex2d(v[0][0], v[0][1]);
	glVertex2d(v[1][0], v[1][1]);
	glEnd();
}

//Renders the entire clock (mins, secs, hours) 
void renderClock() {

	glClear(GL_COLOR_BUFFER_BIT);

	vector<vector<double>> seconds{ {250,250,1},{250,360,1} };

	vector<vector<double>> minutes{ {250,250,1},{380,250,1} };

	vector<vector<double>> hours{ {250,250,1},{250,170,1} };

	vector<vector<double>> stransformed;
	vector<vector<double>> mtransformed;
	vector<vector<double>> htransformed;

	glColor3f(0, 0, 0);
	circle(250, 250, 150);

	cout << sAngle << " " << mAngle << " " << hAngle;

	for (int i = 0; i < seconds.size(); i++) {
		vector<double> temp;
		temp = rotate(seconds[i], sAngle, 250, 250);
		stransformed.push_back(temp);
	}

	for (int i = 0; i < minutes.size(); i++) {
		vector<double> temp;
		temp = rotate(minutes[i], mAngle, 250, 250);
		mtransformed.push_back(temp);
	}

	for (int i = 0; i < hours.size(); i++) {
		vector<double> temp;
		temp = rotate(hours[i], hAngle, 250, 250);
		htransformed.push_back(temp);
	}

	sLine(stransformed);
	mLine(mtransformed);
	hLine(htransformed);

	//printing a BIG BLACK centre point of the clock
	glPointSize(6);
	glColor3f(0, 0, 0);
	glBegin(GL_POINTS);
	glVertex2d(250, 250);
	glEnd();

	glFlush();
}

void mainLoop(int val) {
	sAngle -= 0.1;
	mAngle = sAngle / 63;
	hAngle = mAngle / 63;

	glutPostRedisplay();
	glutTimerFunc(1000, mainLoop, 0);
}


int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Clock");
	myInit();
	glutDisplayFunc(renderClock);
	glutTimerFunc(1000 / FPS, mainLoop, 0);
	glutMainLoop();
	return 0;
}