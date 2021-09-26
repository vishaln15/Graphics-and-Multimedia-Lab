#include <GL/glut.h>
// #include <GL/freeglut.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <cmath>

using namespace std;

class Point {
public:
	int x, y;
};

void myInit(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(0.05);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-600.0, 600.0, -600.0, 600.0);
}

void drawAxis(void){
    glBegin(GL_LINES);
    glVertex2d(-600, 0);
    glVertex2d(600, 0);
    glEnd();
    glBegin(GL_LINES);
    glVertex2d(0, -600);
    glVertex2d(0, 600);
    glEnd();
}

void myDisplay(void){
    double wx_org = 0, wy_org = 0, wx_min = 0, wx_max = 300, wy_min = 0, wy_max = 200;
    double vx_org = 350, vy_org = 0, vx_min = 350, vy_min = 0, vx_max = 500, vy_max = 400;
    double sx = (vx_max - vx_min)/(wx_max - wx_min);
    double sy = (vy_max - vy_min)/(wy_max - wy_min);
    
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    //DDA Line
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.f, 0.f);
    glVertex2f(300.f, 0.f);
    glVertex2f(300.f, 200.f);
    glVertex2f(0.f, 200.f);
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(350.f, 0.f);
    glVertex2f(500.f, 0.f);
    glVertex2f(500.f, 400.f);
    glVertex2f(350.f, 400.f);
    glEnd();

    vector<Point> Shape(4);
    Shape[0].x = 10; Shape[0].y = 10;
    Shape[1].x = 120; Shape[1].y = 10;
    Shape[2].x = 180; Shape[2].y = 110;
    Shape[3].x = 10; Shape[3].y = 70;

    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    for (Point p: Shape)
        glVertex2f(p.x, p.y);
    glEnd();

    vector<Point> Mod_Shape;
    for (Point p: Shape)
    {
        Point newp;
        newp.x = vx_min + (p.x - wx_min) * sx;
        newp.y = vy_min + (p.y - wy_min) * sy;
        Mod_Shape.push_back(newp);
    }

    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    for (Point p: Mod_Shape)
        glVertex2f(p.x, p.y);
    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
    glutCreateWindow("Window Viewport Transformation");
    myInit();
    glutDisplayFunc(myDisplay);
    glutMainLoop();
    return 1;
}