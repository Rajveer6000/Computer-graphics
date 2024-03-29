#include <GL/glut.h>
#include <iostream>
float v[3][2] =
    {
        {0.0, 0.73},
        {1.0, -1.0},
        {-1.0, -1.0}};

int n = 7;

void triangle(float *a, float *b, float *c)
{
    glVertex2fv(a);
    glVertex2fv(b);
    glVertex2fv(c);
}

void divide_triangle(float *a, float *b, float *c, int m)
{
    float v0[2], v1[2], v2[2];
    int j;
    if (m > 0)
    {
        for (j = 0; j < 2; j++)
            v0[j] = (a[j] + b[j]) / 2;
        for (j = 0; j < 2; j++)
            v1[j] = (a[j] + c[j]) / 2;
        for (j = 0; j < 2; j++)
            v2[j] = (b[j] + c[j]) / 2;
        divide_triangle(a, v0, v1, m - 1);
        divide_triangle(c, v1, v2, m - 1);
        divide_triangle(b, v2, v0, m - 1);
    }
    else
        triangle(a, b, c);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    divide_triangle(v[0], v[1], v[2], n);
    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("sierpinski-triangle");
    glutDisplayFunc(display);
    glClearColor(1, 1, 1, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    // init();
    glutMainLoop();
}