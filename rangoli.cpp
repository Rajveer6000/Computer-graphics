#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int a1, b1, count = 0;
void drawEllipse(int a, int b, int q)
{

    glBegin(GL_POINTS);
    int h = 0, k = 0;
    int rx = a;
    int ry = b;
    int x = 0;
    int y = ry;
    int p = ry * ry - rx * rx * ry + rx * rx / 4;

    while (2 * ry * ry * x < 2 * rx * rx * y)
    {
        int ax, ay;
        ax = x * cos(q) - y * sin(q);
        ay = x * sin(q) + y * cos(q);
        int ax1, ay2;
        ax1 = x * cos(q + 1) - y * sin(q + 1);
        ay2 = x * sin(q + 1) + y * cos(q + 1);
        glBegin(GL_POINTS);
        glVertex2i(ax, ay);
        glVertex2i(-ax1, ay2);
        glVertex2i(ax1, -ay2);
        glVertex2i(-ax, -ay);
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
        int ax, ay;
        ax = x * cos(q) - y * sin(q);
        ay = x * sin(q) + y * cos(q);
        int ax1, ay2;
        ax1 = x * cos(q + 1) - y * sin(q + 1);
        ay2 = x * sin(q + 1) + y * cos(q + 1);
        glBegin(GL_POINTS);
        glVertex2i(ax, ay);
        glVertex2i(-ax1, ay2);
        glVertex2i(ax1, -ay2);
        glVertex2i(-ax, -ay);
        glEnd();
        glFlush();


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
    glClearColor(1, 1, 1, 1);
    if (count == 0)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1, 0, 0);
        int h = 400;
        int k = 100;
        glColor3f(0, 0, 1);
        int j = 0,e=0;
        for (int i = 0; ; i++)
        {
            if (e==2)
            {
                e = 0;
                j = 0;
            }
            e++;
            glColor3f(j, 0, 1);
            j++;
            drawEllipse(h, k, i);
        }
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