#include <GL/glut.h>
#include <fstream>
#include <ctime>
#include <iostream>
using namespace std;

int a1, b1, n = 0, t = 0;
int cooridante_X[500];
int cooridante_Y[500];

int get_array(int s1[], int s2[], int n)
{
    if (n != 0)
    {
        int z, k, i, c;
        int t = 0;
        fstream file1;
        file1.open("input.txt", ios ::trunc | ios ::in | ios ::out);
        if (file1)
        {
            for (int i = 1; i <= n; i++)
            {
                file1 << "\n";

                c = rand() % 2;
                z = rand() % 250;
                if (c == 0)
                {
                    z = 0 - z;
                }
                c = rand() % 2;
                k = rand() % 250;
                if (c == 0)
                {
                    k = 0 - k;
                }

                file1 << z << " ";
                file1 << k << " ";
            }
        }
        else
        {
            cout << "Some error occured" << endl;
        }

        file1.seekg(0, ios::beg);
        while (file1)
        {
            file1 >> s2[t];
            file1 >> s1[t];
            t = t + 1;
        }
    }
    else
    {
        cout << "\nvalue of n is zero\n";
    }
    return 0;
}

void myInit()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1, 1, 1, 1.0);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-250, 250, -250, 250);
}

void draw_pixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x + a1, y + b1);
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
void myDisplay()
{
    glColor3f(1, 1, 1);
    draw_line(0, 0, -250, 250);
    draw_line(-250, 250, 0, 0);
    glColor3f(0, 0.5, 0.6);
    for (int k = 0; k < n; k++)
    {
        draw_pixel(cooridante_X[k], cooridante_Y[k]);
    }

    glFlush();
}

int main(int argc, char **argv)
{
    srand(time(0));
    n = rand() % 500;
    get_array(cooridante_Y, cooridante_X, n);
    cout << "points are =: ";

    cout << "{";
    for (int i = 0; i < n; i++)
    {
        cout << "(" << cooridante_X[i] << "," << cooridante_Y[i] << ")";
        cout << ",";
    }
    cout << "}";

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