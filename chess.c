#include <stdio.h>
#include <GL/glut.h>
int a, b, i, j, k, x, y,z;
void myInit()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-500, 500, -500, 500);
}
void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
    a = 0 + x;
    b = 0 + y;
    z = 40;
    for (i = 1; i <= 8; i++)
    {
        for (j = 1; j <= 8; j++)
        {
            k = j + i;
            if (k % 2 == 0)
            {
                glColor3f(0.6, 1,1 );
            }
            else
            {
                glColor3f(0.3,0.3,0.3);
            }
            glBegin(GL_POLYGON);
            glVertex2i(a, b);
            glVertex2i(a + z, b);
            glVertex2i(a + z, b + z);
            glVertex2i(a, b + z);
            glEnd();
            a = a + z;
        }
        a = a - (8*z);
        b = b + z;
    }
    glEnd();
    glFlush();
    return ;
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1000,1000);
    printf("Enter value of origin X1 :");
    scanf("%d", &x);
    printf("Enter value of origin Y1 :");
    scanf("%d", &y);
    glutCreateWindow("hello");
    myInit();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}