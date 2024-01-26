#include <stdio.h>
#include <GL/glut.h>
#include <stdio.h>

float x1, x2, Y1, y2, n;

int screenWidth = 1920;
int screenHeight = 1080;

void getdata()
{
    printf("enter start & end points of line=:");
    scanf("%f", &x1);
    scanf("%f", &Y1);
    scanf("%f", &x2);
    scanf("%f", &y2);
    printf("enter no.s interation =:");
    scanf("%f", &n);
}
void koch(float x1, float Y1, float x2, float y2, float n)
{
    float ang = 60;
    ang = ang * 3.14 / 180;
    float x3 = (2 * x1 + x2) / 3;
    float y3 = (2 * Y1 + y2) / 3;
    float x4 = (x1 + 2 * x2) / 3;
    float y4 = (Y1 + 2 * y2) / 3;

    float x = x3 + (x4 - x3) * 0.5 + (y4 - y3) * 0.8660;
    float y = y3 - (x4 - x3) * 0.8660 + (y4 - y3) * 0.5;
    if (n > 0)
    {
        koch(x1, Y1, x3, y3, n - 1);
        koch(x3, y3, x, y, n - 1);
        koch(x, y, x4, y4, n - 1);
        koch(x4, y4, x2, y2, n - 1);
    }
    
    else
    {
        glBegin(GL_LINE_STRIP);
        glClearColor(1.0, 1.0, 1.0, 0.0);
        glColor3f(0.0, 1.0, 1.0);
        glVertex2f(x1, Y1);
        glVertex2f(x3, y3);
        glVertex2f(x, y);
        glVertex2f(x4, y4);
        glVertex2f(x2, y2);
        glEnd();
    }
}
void Init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    gluOrtho2D(-screenWidth / 4, screenWidth / 4, -screenHeight / 4, screenHeight / 4);
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    koch(x1, Y1, x2, y2, n);
    glFlush();
}
int main(int argv, char **argc)
{
    getdata();

    glutInit(&argv, argc);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("KOCH");
    Init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}