# pragma warning(disable : 4996)
# include <stdio.h>
# include <stdlib.h>
# include <GL/glut.h>
# include <iostream>
# include <vector>

using namespace std;

void initialize() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(5);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-250.0, 250.0, -250.0, 250.0);
}

vector<double> multiply(vector<vector<double>> mat1, vector<double> mat2) {
	vector<double> product(3, 0);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			product[i] += mat1[i][j] * mat2[j];
		}
	}
	return product;
}
vector<double> translate(vector<double> P, double tx, double ty) {
	vector<vector<double>> T(3, vector<double>(3, 0));
	vector<double> product;
	for (int i = 0; i < 3; i++) {
		T[i][i] = 1;
	}
	T[0][2] = tx;
	T[1][2] = ty;
	product = multiply(T, P);
	return product;
}
vector<double> scale(vector<double> P, double sx, double sy) {
	vector<vector<double>> S(3, vector<double>(3, 0));
	vector<double> product;
	S[0][0] = sx;
	S[1][1] = sy;
	S[2][2] = 1;
	product = multiply(S, P);
	return product;
}
vector<double> scale(vector<double> P, double sx, double sy, double fx, double fy) {
	vector<double> product;
	product = translate(P, -fx, -fy);
	product = scale(product, sx, sy);
	product = translate(product, fx, fy);
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
vector<double> rotate(vector<double> P, double theta, double fx, double fy) {
	vector<double> product;
	product = translate(P, -fx, -fy);
	product = rotate(product, theta);
	product = translate(product, fx, fy);
	return product;
}
vector<double> shear(vector<double> P, double shx, double shy) {
	vector<vector<double>> S(3, vector<double>(3, 0));
	vector<double> product;
	for (int i = 0; i < 3; i++) {
		S[i][i] = 1;
	}
	if (shx != 0) {
		S[0][1] = shx;
	}
	if (shy != 0) {
		S[1][0] = shy;
	}
	product = multiply(S, P);
	return product;
}
vector<double> reflect(vector<double> P, char dir) {
	vector<vector<double>> R(3, vector<double>(3, 0));
	vector<double> product;
	for (int i = 0; i < 3; i++) {
		R[i][i] = 1;
	}
	switch (dir) {
	case 'x':
		R[1][1] = -1;
		break;
	case 'y':
		R[0][0] = -1;
		break;
	case 'o':
		R[0][0] = -1;
		R[1][1] = -1;
		break;
	case 'd':
		R[0][0] = 0;
		R[0][1] = 1;
		R[1][1] = 0;
		R[1][0] = 1;
		break;
	}
	product = multiply(R, P);
	return product;
}
void drawRectangle(vector<vector<double>> V) {
	glBegin(GL_QUADS);
	for (int i = 0; i < 4; i++) {
		glVertex2f(V[i][0], V[i][1]);
	}
	glEnd();
}

void drawAxis() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2d(-250, 0);
	glVertex2d(250, 0);
	glVertex2d(0, -250);
	glVertex2d(0, 250);
	glEnd();
}

void compositeDemo() {
	glClear(GL_COLOR_BUFFER_BIT);
	vector<vector<double>> points = {
	{ 50, 50, 1 },
	{ 50, 100, 1 },
	{ 100, 100, 1},
	{ 100, 50, 1}
	};
	vector<vector<double>> points_copy = points;
	vector<vector<double>> transformed;
	int choice = 0;
	double tx = 0, ty = 0, theta = 0, sx = 0, sy = 0, shx = 0, shy = 0, fx = 0, fy = 0;
	char dir = 'x';
	for (int i = 0; i < 2; i++) {
		cout << "-----TRANSFORM " << i + 1 << "----- \n1 - Translate\n2 - Rotate(about origin)\n3 - Rotate(wrt fixed point)\n";
		cout << "4 - Scale (about origin)\n5 - Scale (wrt fixed point)\n6 - Reflect\n7 - Shear\nEnter choice: ";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "\nEnter tx and ty: ";
			cin >> tx >> ty;
			break;
		case 3:
			cout << "\nEnter fx and fy (fixed point): ";
			cin >> fx >> fy;
		case 2:
			cout << "\nEnter theta : ";
			cin >> theta;
			break;
		case 5:
			cout << "\nEnter fx and fy (fixed point): ";
			cin >> fx >> fy;
		case 4:
			cout << "\nEnter sx and sy: ";
			cin >> sx >> sy;
			break;
		case 6:
			cout << "\nReflection wrt to:\n1. x - x axis\n2. y - y axis\n3. o - origin\n4. = - x=y (hit \'=\')\nEnter choice : ";
			cin >> dir;
			break;
		case 7:
			cout << "\nEnter shx and shy: ";
			cin >> shx >> shy;
			break;
		default:
			cout << "Incorrect option\n";
			break;
		}
		for (int i = 0; i < 4; i++) {
			vector<double> temp;
			switch (choice) {
			case 1:
				temp = translate(points[i], tx, ty);
				break;
			case 2:
				temp = rotate(points[i], theta);
				break;
			case 3:
				temp = rotate(points[i], theta, fx, fy);
				break;
			case 4:
				temp = scale(points[i], sx, sy);
				break;
			case 5:
				temp = scale(points[i], sx, sy, fx, fy);
				break;
			case 6:
				temp = reflect(points[i], dir);
				break;
			case 7:
				temp = shear(points[i], shx, shy);
				break;
			}
			transformed.push_back(temp);
		}
		if (i == 0) {
			points = transformed;
			cout << points.size() << "\n";
			transformed.clear();
		}
	}
	drawAxis();
	glColor3f(1.0f, 0.0f, 0.0f);
	drawRectangle(points_copy);
	glColor3f(1.0f, 0.0f, 1.0f);
	drawRectangle(transformed);
	glFlush();
}
int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("2D Composite Transformations");
	glutDisplayFunc(compositeDemo);
	initialize();
	glutMainLoop();
}
