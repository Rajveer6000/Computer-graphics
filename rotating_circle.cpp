#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
#define pi 3.14

float x, y, r = 50, count = 0;
struct point
{
    float x;
    float y;
};

point a[] = {{0, 0}, {50, 50}, {-50, 50}, {-50, -50}, {50, -50}};

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
void display_object()
{

    glBegin(GL_POINTS);

    for (float i = 0; i < (2 * pi); i += 0.001)
    {
        x = r * cos(i);
        y = r * sin(i);

        glVertex2i(x + a[0].x, y + a[0].y);
    }
    draw_line(a[1].x, a[1].y, a[3].x, a[3].y);
    draw_line(a[2].x, a[2].y, a[4].x, a[4].y);
    glEnd();
    glFlush();
}

void animation(int i)
{
    float ax, ay, h = 2, k = 0, q = 5;
    ax = a[i].x;
    ay = a[i].y;
    a[i].x = ((ax * cos(q)) - (ay * sin(q)) + (h * cos(q)) - (k * sin(q)));
    a[i].x = ((ax * sin(q)) + (ay * cos(q)) + (h * sin(q)) + (k * cos(q)));
}
void myDisplay()
{
    if (count == 0)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1, 0, 0);
        glBegin(GL_POINTS);
        glVertex2d(0, 0);
        int j = 0;
        while (j < 1000)
        {
            for (int k = 0; k <= 4; k++)
            {
                animation(k);
            }

            display_object();
            j++;
        }

        glEnd();
        glFlush();
        count++;
    }
}

int main(int argc, char **argv)
{
    // cout << "radius of circle=: ";
    // cin >> r;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("hello");
    gluOrtho2D(-500, 500, -500, 500);
    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0;
}