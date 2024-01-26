#include <stdio.h>
#include <GL/glut.h>
int a, b, i, j, k, x, y, size;
void myInit()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1, 1, 1, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 800, 0, 800);
}
void chess()
{
    a = 0;
    b = 0;
    size = 40;
    for (i = 1; i <= 8; i++)
    {
        for (j = 1; j <= 8; j++)
        {
            k = j + i;
            if (k % 2 == 0)
            {
                glColor3f(0, 0, 1);
            }
            else
            {
                glColor3f(1, 0, 0);
            }
            glBegin(GL_POLYGON);
            glVertex2i(a, b);
            glVertex2i(a + size, b);
            glVertex2i(a + size, b + size);
            glVertex2i(a, b + size);
            glEnd();
            a = a + size;
        }
        a = a - (8 * size);
        b = b + size;
    }
}
void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
    chess();
    glEnd();
    glFlush();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("hello");
    myInit();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}