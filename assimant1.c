#include <GL/glut.h>
#include <stdio.h>

float a, b, a1, b1, r;
int x1, Y1, x2, y2, x3, y3;
void myInit()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-250, 250, -250, 250);
}
void draw_pixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x + a1, y + b1);
    glEnd();
}
void plote_circle_point(float a, float b)
{
    glBegin(GL_POINTS);

    glVertex2f(a + a1, b + b1);
    glEnd();
}
void draw_line(int x1, int x2, int Y1, int y2)
{   
    int dx, dy, i, pk_1;
    int incx, incy, t, t2;
    int x, y;

    dx = x2 - x1;
    dy = y2 - Y1;

    if (dx < 0)
        dx = -dx;
    if (dy < 0)
        dy = -dy;
    incx = 1;
    if (x2 < x1)
        incx = -1;
    incy = 1;
    if (y2 < Y1)
        incy = -1;
    x = x1;
    y = Y1;
    if (dx > dy)
    {
        draw_pixel(x, y);
        pk_1 = 2 * dy - dx;
        t = 2 * (dy - dx);
        t2 = 2 * dy;
        for (i = 0; i < dx; i++)
        {
            if (pk_1 >= 0)
            {
                y += incy;
                pk_1 += t;
            }
            else
                pk_1 += t2;
            x += incx;
            draw_pixel(x, y);
        }
    }
    else
    {
        draw_pixel(x, y);
        pk_1 = 2 * dx - dy;
        t = 2 * (dx - dy);
        t2 = 2 * dx;
        for (i = 0; i < dy; i++)
        {
            if (pk_1 >= 0)
            {
                x += incx;
                pk_1 += t;
            }
            else
                pk_1 += t2;
            y += incy;
            draw_pixel(x, y);
        }
    }
}
void draw_circle(float r)
{ float pk;
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
        if (pk < 0){
            a++;
            pk = pk + t;
        }
        else
        {
            b--;
            pk = pk + t2;
        }
    }
    x3 = a;
    y3 = b;
}
void myDisplay()
{
    draw_circle(r);
    draw_line(0, 0, r, -r);
    draw_line(r, -r, 0, 0);
    draw_line(a, -a, a, -a);
    draw_line(-b, b, b, -b);

    glFlush();
}
int main(int argc, char **argv)
{
    printf("Enter origin (x,y)=: ");
    scanf("%f%f", &a1, &b1);    
    printf("Enter (Radius)=: ");
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