# pragma warning (disable : 4996)
# include <gl/glut.h>
# include <iostream>
# include <stdlib.h>
# include <vector>

const double HEIGHT = 500;
const double WIDTH = -500;

using namespace std;

void initialize() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(5);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 2*HEIGHT, 0, 2*HEIGHT);
}

vector<double> multiply(vector<vector<double>> mat1, vector<double> mat2){
	vector<double> product (3, 0);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			product[i] += mat1[i][j] * mat2[j];
		}
		
	}
	
	return product;
}

vector<double> shear(vector<double> P, double shx, double shy){
	vector<vector<double>> S(3, vector<double>(3, 0));
	vector<double> product;

	for (int i = 0; i < 3; i++)
	{
		S[i][i] = 1;
	}

	S[0][1] = shx;
	S[1][0] = shy;
	
	product = multiply(S, P);
	return product;
}

void triangleToSawtooth(){
    vector<vector<double>> triangleWave1 = {{100, 700, 1},
                                        {200, 800, 1},
                                        {300, 700, 1},
                                        {400, 800, 1},
										{500, 700, 1},
										{600, 800, 1},
										{700, 700, 1},
										{800, 800, 1},
										{900, 700, 1}};

					
	glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINE_STRIP);
    for(int i=0; i<triangleWave1.size(); i++){
        glVertex2d(triangleWave1[i][0], triangleWave1[i][1]);
    }
    glEnd();

	vector<vector<double>> triangleWave = triangleWave1;

	for (int i = 0; i < triangleWave1.size(); i++)
	{
		triangleWave[i][1]-= 400;
	}

	vector<vector<double>> sawtooth;

	double shx = 0.25;

	for (int i = 0; i < triangleWave.size(); i++)
	{
		if (i%2!=0)
		{
			sawtooth.push_back(shear(triangleWave[i], shx, 0));
		}

		else{
			sawtooth.push_back(triangleWave[i]);
		}	
	}

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2d(100, 550);
	glVertex2d(900, 550);
	glEnd();
	
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINE_STRIP);
    for(int i=0; i<sawtooth.size(); i++){
        glVertex2d(sawtooth[i][0], sawtooth[i][1]);
    }
    glEnd();

    glFlush();
}

void drawAxis() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2d(WIDTH, 0);
	glVertex2d(HEIGHT, 0);
	glVertex2d(0, WIDTH);
	glVertex2d(0, HEIGHT);
	glEnd();
	glFlush();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(2*HEIGHT, 2*HEIGHT);
	glutCreateWindow("Triangle to Sawtooth wave");
	glutDisplayFunc(triangleToSawtooth);
	initialize();
	glutMainLoop();
}
