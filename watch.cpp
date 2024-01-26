#include <GL/glut.h>
#include <iostream>
#include <math.h>
using namespace std;
#define pi 3.142857

int a1, b1;

void draw_line(int x1, int Y1, int x2, int y2)
{
    glBegin(GL_POINTS);
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
    glEnd();
    glFlush();
}

void midPointCircleAlgo(int r)
{
    glBegin(GL_POINTS);
    int x, y, i;
    for (i = 0; i < (2 * pi); i += 0.001)
    {
        glBegin(GL_POINTS);

        x = r * cos(i);
        y = r * sin(i);
        glVertex2i(x, y);
        glEnd();

        glFlush();
    }
    glEnd();
    glFlush();
    draw_line(0, 0, r, r);
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);

    midPointCircleAlgo(60);
    // draw_line(0, 0, 50, 50);
    // glEnd();

    // glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("hello");
    // gluOrtho2D(-250, 250, -250, 250);
    gluOrtho2D(-780, 780, -420, 420);

    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0;
}