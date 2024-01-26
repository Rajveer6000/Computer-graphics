#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

void ellipsdraw(int a, int b)
{
    int rx = a;
    int ry = b;
    int x = 0;
    int y = ry;
    int p = ry * ry - rx * rx * ry + rx * rx / 4;

    // Region 1
    while (2 * ry * ry * x < 2 * rx * rx * y)
    {
        glBegin(GL_POINTS);
        glVertex2i(+x, +y);
        glVertex2i(-x, +y);
        glVertex2i(+x, -y);
        glVertex2i(-x, -y);
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

    // Region 2
    p = ry * ry * (x + 0.5) * (x + 0.5) + rx * rx * (y - 1) * (y - 1) - rx * rx * ry * ry;
    while (y > 0)
    {
        glBegin(GL_POINTS);
        glVertex2i(+x, +y);
        glVertex2i(-x, +y);
        glVertex2i(+x, -y);
        glVertex2i(-x, -y);
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
        glFlush();
    }
}
void myDisplay()
{

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 0);
    int h = 300;
    int k = 150;
    for (int i = 0; i < 100; i++)
    {
        ellipsdraw(h, k);
        h = h - 15;
       
    }
    h = 300;
    for (int i = 0; i < 200; i++)
    {
        ellipsdraw(h, k);
        k = k - 15;
        
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("print");
    gluOrtho2D(-500, 500, -500, 500);
    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0;
}