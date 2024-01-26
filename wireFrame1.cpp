#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;

#define PI 3.1416

void setPixel(GLint, GLint);
float ellipse(GLint, GLint, GLint, GLint, GLfloat);
void display();
// void resize(int, int);
int old_xc, old_yc;

void resize(int w, int h)
{
    // set projection paramaters
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, w / 2, 0.0, h / 2);
    glViewport(0.0, 0.0, w, h);
}

float ellipse(GLint xc, GLint yc, GLint rx, GLint ry, GLfloat theta)
{
    GLint x = xc + rx * cos(theta * PI / 180.0);
    GLint y = yc + ry * sin(theta * PI / 180.0);
    setPixel(x, y);
    return x, y;
}

void setPixel(GLint xCoordinate, GLint yCoordinate)
{
    glBegin(GL_POINTS);
    glVertex2i(xCoordinate, yCoordinate);
    glEnd();
}

void draw_line(int x1, int Y1, int x2, int y2)
{

    int dx, dy, i, e;
    int incx, incy, inc1, inc2;
    int x, y;
    incx = 1;
    incy = 1;

    dx = x2 - x1;
    dy = y2 - Y1;

    if (dx < 0)
        dx = -dx;

    if (dy < 0)
        dy = -dy;

    if (x2 < x1)
        incx = -1;

    if (y2 < Y1)
        incy = -1;

    x = x1;
    y = Y1;

    if (dx > dy)
    {
        glVertex2i(x, y);
        e = 2 * dy - dx;
        inc1 = 2 * (dy - dx);
        inc2 = 2 * dy;
        for (i = 0; i < dx; i++)
        {
            if (e >= 0)
            {
                y += incy;
                e += inc1;
            }
            else
                e += inc2;
            x += incx;
            glVertex2i(x, y);
        }
    }
    else
    {
        glVertex2i(x, y);
        e = 2 * dx - dy;
        inc1 = 2 * (dx - dy);
        inc2 = 2 * dx;
        for (i = 0; i < dy; i++)
        {
            if (e >= 0)
            {
                x += incx;
                e += inc1;
            }
            else
                e += inc2;
            y += incy;
            glVertex2i(x, y);
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(2.0);

    GLint xc = 300; // setting the center of globe
    GLint yc = 300;
    GLint theta = 1;
    GLint rx = 100;
    GLint ry = 20;

    while (yc > 100)
    {
        for (GLint theta = 1; theta <= 360; theta++)
        {
            GLint x = xc + rx * cos(theta * PI / 180.0);
            GLint y = yc + ry * sin(theta * PI / 180.0);
            setPixel(x, y);
        }

        yc = yc - 10;
        old_yc = yc;
        draw_line(xc, yc, xc, old_yc);
    }

    rx = 20;
    ry = 100;

    while (xc > 100)
    {
        for (GLint theta = 1; theta <= 360; theta++)
        {
            GLint x = xc + rx * cos(theta * PI / 180.0);
            GLint y = yc + ry * sin(theta * PI / 180.0);
            setPixel(x, y);
        }

        xc = xc - 10;
        old_xc = xc;
        draw_line(xc, yc, old_xc, yc);
    }

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);                       // initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // initialize display mode
    glutInitWindowSize(1000, 1000);              // set display-window width & height
    glutInitWindowPosition(500, 500);            // set display-window upper-left position

    glutCreateWindow("Wire Frame Model of Globe"); // create display- window

    glutDisplayFunc(display); // call graphics to be displayed on the window
    glutReshapeFunc(resize);  // calls whenever frame buffer window is resized
    glutMainLoop();           // display everything and wait
}