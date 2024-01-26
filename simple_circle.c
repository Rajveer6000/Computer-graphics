#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#define pi 3.142857
int x, y, r;
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    
    for (float i = 0; i < (2 * pi); i += 0.001)
    {
        x = 200 * cos(i);
        y = 200 * sin(i);

        glVertex2i(x, y);
    }
    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1366, 768);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Circle Drawing");
    gluOrtho2D(-780, 780, -420, 420);
    glutDisplayFunc(display);
    glutMainLoop();
}