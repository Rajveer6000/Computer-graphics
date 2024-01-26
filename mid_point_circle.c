#include <GL/glut.h>
#include <stdio.h>

float a, b, a1, b1, r;

void myInit()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-250, 250, -250, 250);
}

void plote_circle_point(float a, float b)
{
    glBegin(GL_POINTS);

    glVertex2f(a + a1, b + b1);
    glEnd();
}

void draw_circle(float r)
{
    float i, pk;
    float t, t2;
    a = 0;
    b = r;
    pk = (5 / 4) - r;

    while (b > a)
    {
        plote_circle_point(a, b);
        plote_circle_point(-a, -b);
        plote_circle_point(-b, a);
        plote_circle_point(b, -a);
        a++;
        t = (2 * a) + 1;
        t2 = (2 * a) + 1 - (2 * b);
        if (pk < 0)
        {
            a++;
            pk = pk + t;
        }
        else
        {
            b--;
            pk = pk + t2;
        }
    }
   
}

void myDisplay()
{
    draw_circle(r);
    glFlush();
}

int main(int argc, char **argv)
{

    printf("Enter origin (x,y)=: ");
    scanf("%f%f", &a1, &b1);

    printf("Enter (Radius)");
    scanf("%f", &r);

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