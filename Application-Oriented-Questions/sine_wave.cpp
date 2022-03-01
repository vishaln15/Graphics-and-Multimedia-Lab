#include <stdlib.h>
#include <iostream>
#include <vector>
#include <gl/glut.h>
#include <Windows.h>

using namespace std;

const int FPS = 5;
int j = 1;

void myInit() {
    glClearColor(1, 1, 1, 0);
    glColor3f(0, 0, 0);
    glPointSize(1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

void plot(int x, int y) {
    glColor3f(1, 0, 0);
    glBegin(GL_POINTS);
    glVertex2d(x, y);
    glEnd();
}

void drawUpperWave(int x_centre, int y_centre, int r) {

    int x = r, y = 0;
    int p = 1 - r;

    while (x > y)
    {
        y++;
        if (p <= 0) {
            p += 2 * y + 1;
        }

        else {
            x--;
            p += 2 * y - 2 * x + 1;
        }

        plot(x + x_centre, y + y_centre);
        plot(-x + x_centre, y + y_centre);
        plot(y + x_centre, x + y_centre);
        plot(-y + x_centre, x + y_centre);
    }

}

void drawLowerWave(int x_centre, int y_centre, int r) {

    int x = r, y = 0;
    int p = 1 - r;

    while (x > y)
    {
        y++;
        if (p <= 0) {
            p += 2 * y + 1;
        }

        else {
            x--;
            p += 2 * y - 2 * x + 1;
        }

        plot(x + x_centre, -y + y_centre);
        plot(-x + x_centre, -y + y_centre);
        plot(y + x_centre, -x + y_centre);
        plot(-y + x_centre, -x + y_centre);
    }
}

void drawAxis() {
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2d(50, 250);
    glVertex2d(450, 250);
    glEnd();
    glBegin(GL_LINES);
    glVertex2d(50, 200);
    glVertex2d(50, 300);
    glEnd();
}

void drawSine() {
    glClear(GL_COLOR_BUFFER_BIT);
    cout << j << endl;
    drawAxis();
    vector<vector<int>> centres = {{100, 250, 50, 1*j},
                                   {200, 250, 50, -1*j},
                                   {300, 250, 50, 1*j},
                                   {400, 250, 50, -1*j}};

    for (int i = 0; i < centres.size(); i++)
    {
        if (centres[i][3] == 1)
    {
        drawUpperWave(centres[i][0], centres[i][1], centres[i][2]);

    }

    else {
        drawLowerWave(centres[i][0], centres[i][1], centres[i][2]);
        }
    }
    glutPostRedisplay();
}

void mainLoop(int val){
    drawSine();
    j*=-1; 
    glutTimerFunc(1000/FPS, mainLoop, 0);
    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Sine Wave Generation");
    myInit();
    glutDisplayFunc(drawSine);
    glutTimerFunc(1000/FPS, mainLoop, 0);
    glutMainLoop();
    return 0;
}