#include <iostream>
#include <GL/glut.h>
using namespace std;

GLfloat vertices[3][2] = {{-100.0, -100.0}, {100.0, -100.0}, {0.0, 100.0}};
int n;

void drawTriangle(GLfloat *a, GLfloat *b, GLfloat *c)
{
    glBegin(GL_TRIANGLES);
    glVertex2fv(a);
    glVertex2fv(b);
    glVertex2fv(c);
    glEnd();
}

void divideTriangle(GLfloat *a, GLfloat *b, GLfloat *c, int k)
{
    GLfloat mid[2];
    if (k > 0)
    {
        for (int j = 0; j < 2; j++)
            mid[j] = (a[j] + b[j]) / 2;
        divideTriangle(a, mid, c, k - 1);
        divideTriangle(b, mid, c, k - 1);
        divideTriangle(a, b, mid, k - 1);
    }
    else
    {
        drawTriangle(a, b, c);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    GLfloat v[3][2] = {{-100.0, -100.0}, {100.0, -100.0}, {0.0, 100.0}};
    divideTriangle(v[0], v[1], v[2], n);
    glFlush();
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-250, 250, -250, 250);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    printf("Enter the number of recursive steps: ");
    scanf("%d", &n);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Sierpinski Gasket");

    glutDisplayFunc(display);
    glutReshapeFunc(myReshape);

    // glClearColor(1.0, 1.0, 1.0, 1.0);
    // glColor3f(0.0, 0.0, 0.0);

    glutMainLoop();
    return 0;
}
