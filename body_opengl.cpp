#include <GL/glut.h>
#include <iostream>

int a1, b1;
void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    glColor3f(1, 1, 0);


    glVertex2i(0, 0);
    glVertex2i(-40, 40);
    glVertex2i(40, 40);
    glVertex2i(40, -40);
    glVertex2i(-40, -40);
    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("hello");
    gluOrtho2D(-250, 250, -250, 250);
    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0;
}