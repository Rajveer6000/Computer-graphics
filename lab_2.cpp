#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

float v[3][2] =
    {
        {200, 300},
        {400, 0},
        {0, 0}};
struct point
{
    float x;
    float y;
};
point a[] = {{200, 300},
             {400, 0},
             {0, 0}};
float v1[3][2] =
    {
        {0, 0}, {0, 0}, {0, 0}};
void triangle(float *a, float *b, float *c)
{
    glVertex2fv(a);
    glVertex2fv(b);
    glVertex2fv(c);
}
void drawLine(float x1, float Y1, float x2, float y2)
{
    glBegin(GL_LINES);
    glVertex2f(x1, Y1);
    glVertex2f(x2, y2);
    glEnd();
}
void divide_triangle(float *a, float *b, float *c, int iterations)
{
    float v0[2], v1[2], v2[2];
    int j;
    if (iterations > 0)
    {
        for (j = 0; j < 2; j++)
            v0[j] = (a[j] + b[j]) / 2;
        for (j = 0; j < 2; j++)
            v1[j] = (a[j] + c[j]) / 2;
        for (j = 0; j < 2; j++)
            v2[j] = (b[j] + c[j]) / 2;
        divide_triangle(a, v0, v1, iterations - 1);
        divide_triangle(c, v1, v2, iterations - 1);
        divide_triangle(b, v2, v0, iterations - 1);
    }
    else
        triangle(a, b, c);
}

void drawKoch(float x1, float y1, float x2, float y2, float iterations)
{
    if (iterations == 0)
    {
        drawLine(x1, y1, x2, y2);
    }
    else
    {
        float deltaX = (x2 - x1) / 3.0;
        float deltaY = (y2 - y1) / 3.0;

        float xA = x1 + deltaX;
        float yA = y1 + deltaY;

        float xC = 0.5 * (x1 + x2) + sqrt(3) * (y1 - y2) / 6.0;
        float yC = 0.5 * (y1 + y2) + sqrt(3) * (x2 - x1) / 6.0;

        float xD = x2 - deltaX;
        float yD = y2 - deltaY;

        drawKoch(x1, y1, xA, yA, iterations - 1);
        drawKoch(xA, yA, xC, yC, iterations - 1);
        drawKoch(xC, yC, xD, yD, iterations - 1);
        drawKoch(xD, yD, x2, y2, iterations - 1);
    }
}
void display_object()
{
    glColor3f(0, 1, 0);
    float iterations = 10;
    divide_triangle(v[0], v[1], v[2], iterations);
    glColor3f(0, 1, 1);
    drawKoch(v[2][0], v[2][1], v[0][0], v[0][1], iterations);
    glColor3f(1, 1, 0);
    drawKoch(v[0][0], v[0][1], v[1][0], v[1][1], iterations);
    glColor3f(1, 0, 0);
    drawKoch(v[1][0], v[1][1], v[2][0], v[2][1], iterations);
}
void Rotation(float q, float x1, float y1, float *z, float *b, float *c)
{
    glColor3f(0, 1, 0);

    float ax, ay;
    ax = z[0] - x1;
    ay = z[1] - y1;
    a[0].x = x1 + ax * cos(q) - ay * sin(q);
    a[0].y = y1 + ax * sin(q) + ay * cos(q);
    ax = 0, ay = 0;
    ax = b[0] - x1;
    ay = b[1] - y1;
    a[1].x = x1 + ax * cos(q) - ay * sin(q);
    a[1].y = y1 + ax * sin(q) + ay * cos(q);
    ax = c[0] - x1;
    ay = c[1] - y1;
    a[2].x = x1 + ax * cos(q) - ay * sin(q);
    a[2].y = y1 + ax * sin(q) + ay * cos(q);

    cout << "(" << a[0].x << "," << a[0].y << ")\n";
    cout << "(" << a[1].x << "," << a[1].y << ")\n";
    cout << "(" << a[2].x << "," << a[2].y << ")\n";

    cout << "\n\n";
}
void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    display_object();
    Rotation(2, 0, 0, v[0], v[1], v[2]);
    // display_object();
    glColor3f(0, 1, 0);
    float iterations = 10;
    for (int i = 0; i < 3; i++)
    {
        v1[i][0] = a[i].x;
        v1[i][1] = a[i].y;
        cout << v1[i][0]<<"\n";
        cout << v1[i][1]<<"\n";
    }

    divide_triangle(v1[0], v1[1], v1[2], iterations);
    glColor3f(0, 1, 1);
    drawKoch(a[2].x, a[2].y, a[0].x, a[0].y, iterations);
    glColor3f(1, 1, 0);
    drawKoch(a[0].x, a[0].y, a[1].x, a[1].y, iterations);
    glColor3f(1, 0, 0);
    drawKoch(a[1].x, a[1].y, a[2].x, a[2].y, iterations);

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("lab_q2");
    gluOrtho2D(-500, 500, -500, 500);
    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0;
}