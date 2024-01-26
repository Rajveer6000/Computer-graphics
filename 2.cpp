#include <GL/glut.h>
#include <iostream>
#include <math.h>
using namespace std;

int pix_color[3] = {0};
int b_color[30] = {0, 1, 1}, f_color[3] = {1, 0, 0};
int z = 150, l = 100;
void draw_line(int x1, int x2, int Y1, int y2)
{
    int dx, dy, i, e;
    int incx, incy, inc1, inc2;
    int x, y;

    dx = x2 - x1;
    dy = y2 - Y1;

    if (dx < 0)
        dx = -dx;
    if (dy < 0)
        dy = -dy;
    incx = 1;
    if (x2 < x1)
        incx = -1;
    incy = 1;
    if (y2 < Y1)
        incy = -1;
    x = x1;
    y = Y1;
    glBegin(GL_POINTS);

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
}

bool chekcolor(int x_color[3], int y_color[3])
{
    return (x_color[0] == y_color[0] && x_color[1] == y_color[1] && x_color[2] == y_color[2]);
}

void filling(int x, int y, int b_color[], int F_color[])
{
    glReadPixels(x, y, 1, 1, GL_RGB, GL_INT, pix_color);

    if (!chekcolor(b_color, pix_color) && !chekcolor(f_color, pix_color))
    {
        glColor3f(1, 0, 0);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();

        // cout << x << " " << y << "\n";
        filling(x + 1, y, b_color, f_color);
        filling(x - 1, y, b_color, f_color);
        filling(x, y - 1, b_color, f_color);
        filling(x, y - 1, b_color, f_color);
    }
    return;
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 1.0);
    glPointSize(1.0);

    glBegin(GL_POINTS);

    draw_line(z, (z + l), z, z);
    draw_line((z + l), (z + l), z, (z + l));
    draw_line((z + l), z, (z + l), (z + l));
    draw_line(z, z, z, (z + l));
    glEnd();
    glFlush();
    filling(z + 1, z + 1, b_color, f_color);

    // filling();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(700, 100);

    glutCreateWindow("hello");
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0;
}