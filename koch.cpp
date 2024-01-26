#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;
#define pi 3.14159265359
void drawLine(float x1, float Y1, float x2, float y2)
{
    glBegin(GL_LINES);
    glVertex2f(x1, Y1);
    glVertex2f(x2, y2);
    glEnd();
}

void drawKoch(float x1, float y1, float x2, float y2, int iterations)
{
    if (iterations == 0)
    {
        drawLine(x1, y1, x2, y2);
    }
    else
    {

        float deltaX = (x2 - x1) / 3.0;
        float deltaY = (y2 - y1) / 3.0;

        float xA = x1 + deltaX;
        float yA = y1 + deltaY;

        float xB = x1 + 2 * deltaX;
        float yB = y1 + 2 * deltaY;

        float xC = 0.5 * (x1 + x2) + sqrt(3) * (y1 - y2) / 6.0;
        float yC = 0.5 * (y1 + y2) + sqrt(3) * (x2 - x1) / 6.0;

        float xD = x2 - deltaX;
        float yD = y2 - deltaY;

        drawKoch(x1, y1, xA, yA, iterations - 1);
        drawKoch(xA, yA, xC, yC, iterations - 1);
        drawKoch(xC, yC, xB, yB, iterations - 1);
        drawKoch(xB, yB, xD, yD, iterations - 1);
        drawKoch(xD, yD, x2, y2, iterations - 1);
    }
}
void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    glColor3f(1, 0, 1);
    float x1 = -500, y1 = 0;
    float x2 = 500, y2 = 0;
    int iterations = 5;
    drawKoch(x1, y1, x2, y2, iterations);
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("koch");
    gluOrtho2D(-500, 500, -500, 500);
    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0;
}