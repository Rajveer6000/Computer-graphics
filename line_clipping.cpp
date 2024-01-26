#include <GL/glut.h>
#include <iostream>
using namespace std;

void draw_line(int x1, int x2, int Y1, int y2)
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

int check_region(int x, int y)
{
    if (y >= 350 && x < 150)
    {
        return 9;
    }
    else if (y > 350 && x < 350 && x >= 150)
    {
        return 1;
    }
    else if (x >= 350 && y >= 350)
    {
        return 5;
    }
    else if (x < 150 && y < 350 && y >= 150)
    {
        return 8;
    }
    else if (x <= 350 && x >= 150 && y <= 350 && y >= 150)
    {
        return 0;
    }
    else if (x > 350 && y >= 150 && y < 350)
    {
        return 4;
    }
    else if (x < 150 && y < 150)
    {
        return 10;
    }
    else if (x < 350 && x >= 150 && y < 150)
    {
        return 2;
    }
    else
    {
        return 6;
    }
}

int condition(int a, int b)
{
    int z = a | b;
    int q = a & b;
    if (z == 0)
    {
        return 0;
    }
    else
    {
        if (q != 0)
        {
            return 1;
        }
        else
        {
            return 2;
        }
    }
}

void clipping(int x1, int y1, int x2, int y2)
{
    int l, k, q, o;
    int a1, b1, a2, b2;
    float dx;
    dx = float(float(y2 - y1) / float(x2 - x1));

    l = check_region(x1, y1);
    k = check_region(x2, y2);
    q = condition(l, k);
    if (q !=1)
    {
        cout << "partialy visible \n";
        if (x1 <= 150 && x2 > 150)
        {
            x1 = 150;
            y1 = y2 - (dx * (x2 - x1));
        }
        if (x1 <= 350 && x2 > 350)
        {
            x2 = 350;
            y2 = y1 + (dx * (x2 - x1));
        }
        l = check_region(x1, y1);
        k = check_region(x2, y2);
        q = condition(l, k);
        if (q == 2)
        {

            if (dx >= 0)
            {
                if (y1 <= 150 && y2 > 150)
                {
                    y1 = 150;
                    x1 = x2 - ((y2 - y1) / dx);
                }
                if (y1 <= 350 && y2 > 350)
                {
                    y2 = 350;
                    x2 = x1 + ((y2 - y1) / dx);
                }
            }
            else
            {
                if (y2 <= 150 && y1 > 150)
                {
                    y2 = 150;
                    x2 = x1 + ((y2 - y1) / dx);
                }
                if (y2 <= 350 && y1 > 350)
                {
                    y1 = 350;
                    x1 = x2 - ((y2 - y1) / dx);
                }
            }
            glColor3f(1, 0, 1);
            glBegin(GL_POINTS);
            draw_line(x1, x2, y1, y2);
            glEnd();
            glFlush();
        }
        if (q == 0)
        {
            glColor3f(1, 0, 1);
            glBegin(GL_POINTS);
            draw_line(x1, x2, y1, y2);
            glEnd();
            glFlush();
        }
    }
    else
    {
        cout << q << "completely not visible \n";
    }
}

void myDisplay()
{
    int z;
    cout << "\n\n";

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    glBegin(GL_POINTS);
    draw_line(0, 500, 150, 150);
    draw_line(0, 500, 350, 350);
    draw_line(150, 150, 0, 500);
    draw_line(350, 350, 0, 500);
    glColor3f(0, 1, 0);

    // draw_line(30, 325, 170, 450);
    // draw_line(0, 400, 0, 400);
    // draw_line(200, 400, 250, 400);
    // draw_line(10, 400, 400, 200);
    // draw_line(10, 200, 190, 90);
    // draw_line(140, 450, 450, 170);
    // draw_line(0, 450, 0, 170);
    // draw_line(0, 400, 0, 200);
    // draw_line(160,340,340,160);
    // draw_line(250,250,0,400);
    glEnd();
    glFlush();

    clipping(30, 170, 325, 450);
    clipping(0, 0, 400, 400);
    clipping(200,250, 400, 400);
    clipping(10, 400, 400, 200);
    clipping(10, 190, 200, 90);
    clipping(140, 450, 450, 170);
    clipping(0, 0, 450, 170);
    clipping(0, 0, 400, 200);
    clipping(160,340,340,160);
    clipping(250,0,250,400);
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