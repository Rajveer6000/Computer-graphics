#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int a1, b1, count = 0;

void drawEllipse(int a, int b, int h, int k)
{
    int rx = a;
    int ry = b;
    int x = 0;
    int y = ry;
    int p = ry * ry - rx * rx * ry + rx * rx / 4;

    while (2 * ry * ry * x < 2 * rx * rx * y)
    {
        glBegin(GL_POINTS);
        glVertex2i(h + x, k + y);
        glVertex2i(h - x, k + y);
        glVertex2i(h + x, k - y);
        glVertex2i(h - x, k - y);
        glEnd();

        if (p < 0)
        {
            x++;
            p += 2 * ry * ry * x + ry * ry;
        }
        else
        {
            x++;
            y--;
            p += 2 * ry * ry * x - 2 * rx * rx * y + ry * ry;
        }
    }

    p = ry * ry * (x + 0.5) * (x + 0.5) + rx * rx * (y - 1) * (y - 1) - rx * rx * ry * ry;
    while (y > 0)
    {
        glBegin(GL_POINTS);
        glVertex2i(h + x, k + y);
        glVertex2i(h - x, k + y);
        glVertex2i(h + x, k - y);
        glVertex2i(h - x, k - y);
        glEnd();

        if (p > 0)
        {
            y--;
            p += -2 * rx * rx * y + rx * rx;
        }
        else
        {
            x++;
            y--;
            p += 2 * ry * ry * x - 2 * rx * rx * y + rx * rx;
        }
    }
}
void myDisplay()
{
    if (count == 0)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1, 1, 0);
        glBegin(GL_POINTS);
        int h = 200;
        int k = 50;
        for (int i = 0; i < 22; i++)
        {
            drawEllipse(h, k, 0, 0);
            h = h - 10;
            k = k + 10;
        }
        glColor3f(1, 1, 0);

        h = 50;
        k = 200;
        for (int i = 0; i < 22; i++)
        {
            drawEllipse(h, k, 0, 0);
            h = h + 10;
            k = k - 10;
        }

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