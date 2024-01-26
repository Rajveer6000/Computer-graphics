#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

GLfloat oldx = 0, oldy = 0;
void koch(GLdouble dir, GLfloat len, GLint itr)
{ 
    GLfloat newx;
    GLfloat newy;
    GLdouble rdir = 3.14159265358979323846 / 180.0 * dir;
    newx = oldx + len * cos(rdir);
    newy = oldy + len * sin(rdir);

    if (itr == 0)
    {
        glVertex2f(oldx, oldy);
        glVertex2f(newx, newy);
        oldx = newx;
        oldy = newy;
    }

    else
    {
        itr--;
        koch(dir, len, itr);
        dir += 60;
        koch(dir, len, itr);
        dir -= 120;
        koch(dir, len, itr);
        dir += 60;
        koch(dir, len, itr);
    }
}

GLfloat i = 3;
void display()
{
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    koch(0, 2, i);
    koch(-120, 2, i);
    koch(120, 2, i);
    glEnd();
    glFlush();
}

void mouse(int button, int state, int x, int y)
{

    if (button == GLUT_RIGHT_BUTTON)
        i++;
    if (button == GLUT_LEFT_BUTTON)
    {
        oldx = x;
        oldy = y;
        display();
    }
    if (button == GLUT_MIDDLE_BUTTON)
    {
        i = 3;
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
    }
}
void keyborard(unsigned char key, int x, int y)
{
    if (key == 'i')
        i++;
    if (key == 'd')
        i--;

    if (key == 'p')
    {
        oldx = x;
        oldy = y;
        display();
    }
    if (key == 'c')
    {
        i = 3;
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(1000, 1000);

    glutCreateWindow("Fractal");
    gluOrtho2D(0, 1000, 1000, 0);
    glClearColor(1, 1, 1, 0);

    glClearDepth(1);
    glClear(GL_COLOR_BUFFER_BIT);
    cout << "Left mouse button to draw Koch's Snowflake.\nRight Mouse button to increase the iterations.\nMiddle mouse button to clear the screen.\n";
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyborard);
    glutMainLoop();
    return 0;
}