#include <GL/glut.h>
#include <stdio.h>

float a1, b1, a2, b2, t;
float a, b;

void myInit()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-250, 250, -250, 250);
}



void draw_line(float a1, float a2, float b1, float b2)
{
    glBegin(GL_POINTS);
    float dx, dy, i, pk;
    float incx, incy, t, t2;

    if (a1 > a2)
    {
        t = a1;
        a1 = a2;
        a2 = t;
        t = a;
        b1 = b2;
        b2 = t;
    }
    dx = a2 - a1;
    dy = b2 - b1;
    a = a1;
    b = b1;
    if (dx > dy)
    {
        glVertex2d(a,b);
        glEnd();
        pk = 2 * dy - dx;
        t = 2 * (dy - dx);
        t2 = 2 * dy;
        for (i = 0; i < dx; i++)
        {
            if (pk >= 0)
            {
                b++;
                pk += t;
            }
            else
                pk += t2;
            a++;
            glVertex2d(a,b);
            glEnd();
        }
    }
    else
    {
        glVertex2d(a,b);
        glEnd();
        pk = 2 * dx - dy;
        t = 2 * (dx - dy);
        t2 = 2 * dx;
        for (i = 0; i < dy; i++)
        {
            if (pk >= 0)
            {
                a++;
                pk += t;
            }
            else
                pk += t2;
            b++;
            glVertex2d(a,b);
            glEnd();
        }
    }
}

void myDisplay()
{
    draw_line(a1, a2, b1, b2);
    glFlush();
}

int main(int argc, char **argv)
{

    printf("Enter (a1, b1, a2, b2) =:");
    scanf("%f %f %f %f", &a1, &b1, &a2, &b2);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("hello");
    myInit();
    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0;
}