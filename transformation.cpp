#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int a1, b1, count = 0;
// vector<int> vect;
struct point
{
    int x;
    int y;
};
point a[] = {{10, 110}, {10, 10}, {110, 10}, {110, 110}, {60, 210}, {10, 110}, {110, 110}};

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
void display_object(int n)
{

    for (int i = 0; i < n; i++)
    {
        draw_line(a[i].x, a[i].y, a[i + 1].x, a[i + 1].y);
    }
}
void Translation(int x, int y, int n)
{
    glColor3f(0, 1, 0);
    for (int i = 0; i <= n; i++)
    {
        a[i].x = a[i].x + x;
        a[i].y = a[i].y + y;
        cout << "(" << a[i].x << "," << a[i].y << ")\n";
    }
    cout << "\n\n";
    display_object(6);
}
void Scaling(int sx, int sy, int n)
{
    glColor3f(0, 0, 1);
    for (int i = 0; i <= n; i++)
    {
        a[i].x = a[i].x * sx;
        a[i].y = a[i].y * sy;
        cout << "(" << a[i].x << "," << a[i].y << ")\n";
    }
    cout << "\n\n";
    display_object(6);
}
void Rotation(int q, int n, int x1, int y1)
{
    glColor3f(0, 1, 0);
    for (int i = 0; i <= n; i++)
    {
        int ax, ay;
        ax = a[i].x - x1;
        ay = a[i].y - y1;
        a[i].x = x1 + ax * cos(q) - ay * sin(q);
        a[i].y = y1 + ax * sin(q) + ay * cos(q);

        cout << "(" << a[i].x << "," << a[i].y << ")\n";
    }
    cout << "\n\n";
    display_object(6);
}
void Reflection(int n)
{
    glColor3f(0, 1, 0);
    for (int i = 0; i <= n; i++)
    {
        int ax, ay;
        ax = a[i].x;
        ay = a[i].y;
        a[i].x = -ax;
        a[i].y = -ay;
        cout << "(" << a[i].x << "," << a[i].y << ")\n";
    }
    cout << "\n\n";
    display_object(6);
}
void Shearing(int h, int g, int n)
{
    glColor3f(0, 0, 1);
    for (int i = 0; i <= n; i++)
    {
        int ax, ay;
        ax = a[i].x;
        ay = a[i].y;
        a[i].x = ax + h * ay;
        a[i].y = g * ax + ay;

        cout << "(" << a[i].x << "," << a[i].y << ")\n";
    }
    cout << "\n\n";
    display_object(6);
}

void myDisplay()
{
    if (count == 0)
    {
        glClearColor(1,1,1, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1, 0, 0);
        glBegin(GL_POINTS);
        glVertex2d(0, 0);
        // object print
        display_object(6);
        // translation
        Translation(50, 50, 6);
        // rotation
        Rotation(45, 6, 60, 60);
        // scaling
        Scaling(2, 2, 6);
        // reflection
        Reflection(6);

        // shearing
        Shearing(1, 0, 6);

        glEnd();
        glFlush();
        count++;
    }
}

int main(int argc, char **argv)
{
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