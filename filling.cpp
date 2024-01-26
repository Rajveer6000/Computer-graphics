#include <GL/glut.h>
#include <iostream>
#include <math.h>
#define pi 3.142857
using namespace std;

float pix_color[3] = {0.0};
float b_color[3] = {1.0, 1.0, 1.0}, fc[3] = {1.0, 1.0, 0.0}, fc1[3] = {1.0, 0.0, 1.0}, fc2[3] = {0.0, 0.0, 1.0};
float z = 200, l = 200, r = 25;

void draw_line(int x1, int x2, int Y1, int y2)
{

    int dx, dy, i, e;
    int incx, incy, inc1, inc2;
    int x, y;
    incx = 1;
    incy = 1;

    dx = x2 - x1;
    dy = y2 - Y1;

    if (dx < 0)
        dx = -dx;

    if (dy < 0)
        dy = -dy;

    if (x2 < x1)
        incx = -1;

    if (y2 < Y1)
        incy = -1;

    x = x1;
    y = Y1;

    if (dx > dy)
    {
        glVertex2i(x, y);
        e = 2 * dy - dx;
        inc1 = 2 * (dy - dx);
        inc2 = 2 * dy;
        for (i = 0; i < dx; i++)
        {
            if (e >= 0)
            {
                y += incy;
                e += inc1;
            }
            else
                e += inc2;
            x += incx;
            glVertex2i(x, y);
        }
    }
    else
    {
        glVertex2i(x, y);
        e = 2 * dx - dy;
        inc1 = 2 * (dx - dy);
        inc2 = 2 * dx;
        for (i = 0; i < dy; i++)
        {
            if (e >= 0)
            {
                x += incx;
                e += inc1;
            }
            else
                e += inc2;
            y += incy;
            glVertex2i(x, y);
        }
    }
}

bool chekcolor(float x_color[3], float y_color[3])
{
    return (x_color[0] == y_color[0] && x_color[1] == y_color[1] && x_color[2] == y_color[2]);
}

void filling(int x, int y, float bc[], float fc[])
{

    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, pix_color);

    if (!chekcolor(bc, pix_color) && !chekcolor(fc, pix_color))
    {
        glColor3fv(fc);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();

        filling(x + 1, y, bc, fc);
        filling(x - 1, y, bc, fc);
        filling(x, y + 1, bc, fc);
        filling(x, y - 1, bc, fc);
    }

    return;
}

void myDisplay()
{
    float a = 0.0, b = 0.0;
    float x = 0, y = 0;
    
    glClear(GL_COLOR_BUFFER_BIT);
    cout << "Done \n";
    glColor3fv(b_color);
    glPointSize(1.0);
//square
    glBegin(GL_POINTS);
    draw_line(z, (z + l), z, z);
    draw_line((z + l), (z + l), z, (z + l));
    draw_line((z + l), z, (z + l), (z + l));
    draw_line(z, z, z, (z + l));
    glEnd();
// small square
    glBegin(GL_POINTS);
    draw_line((z + (l / 4)), (z + (3 * (l / 4))), (z + (l / 4)), (z + (l / 4)));
    draw_line((z + (l / 4)), (z + (3 * (l / 4))), (z + (l / 4) + 15), (z + (l / 4)) + 15);
    draw_line((z + (l / 4)), (z + (l / 4)), (z + (l / 4)), (z + (l / 4) + 15));
    draw_line((z + (3 * (l / 4))), (z + (3 * (l / 4))), (z + (l / 4)), (z + (l / 4)) + 15);

    glEnd();
//triangle
    glBegin(GL_POINTS);

    draw_line((z + (3 * (l / 8))), (z + (5 * (l / 8))), (z + (3 * (l / 8))), (z + (3 * (l / 8))));
    draw_line((z + (3 * (l / 8))), (z + ((l / 2))), (z + (3 * (l / 8))), (z + (6 * (l / 8))));
    draw_line((z + (5 * (l / 8))), (z + ((l / 2))), (z + (3 * (l / 8))), (z + (6 * (l / 8))));

    glEnd();
// circle 1

    a = z + (l / 4);
    b = z + (3 * (l / 4));
    glBegin(GL_POINTS);
    for (float i = 0; i < (2 * pi); i += 0.001)
    {
        x = a + (r * cos(i));
        y = b + (r * sin(i));

        glVertex2i(x, y);
    }
    glEnd();
// circle 2
    a = z + (3 * (l / 4));
    b = z + (3 * (l / 4));
    x = 0, y = 0;
    glBegin(GL_POINTS);
    for (float i = 0; i < (2 * pi); i += 0.001)
    {
        x = a + (r * cos(i));
        y = b + (r * sin(i));

        glVertex2i(x, y);
    }
    glEnd();

    glFlush();
//calling filling algo for eye left
    filling(z + ((l / 4)) + 1, z + (3 * (l / 4)) + 1, b_color, fc);
    glFlush();

//calling filling algo for eye right
    filling(z + (3*(l / 4)) + 1, z + (3 * (l / 4)) + 1, b_color, fc);
    glFlush();

//calling filling algo for small square
    filling(z + l / 4 + 1, z + l / 4 + 1, b_color, fc1);
    glFlush();

//calling filling algo for triangle
    filling(z + (3 * (l / 8)) + 5, z + (3 * (l / 8)) + 5, b_color, fc1);
    glFlush();

//calling filling algo for square
    // filling(z + 1, z + 1, b_color, fc);
    // filling(z + 1, z + 1, b_color, fc1);
    filling(z + 1, z + 1, b_color, fc2);
    glFlush();
    return ;
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(700, 100);

    glutCreateWindow("hello");
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0;
}