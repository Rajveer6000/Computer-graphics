#include <GL/glut.h>
#include <cmath>

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glColor3ub(255, 0, 0);
    glBegin(GL_POINTS);
     for (float x = 0; x <= 1000; x += 0.1)  // Adjusted loop range for x
    {
        float x_original = (x / 1000.0) * 4.0 - 2.0;  // Normalize x to the range [-2, 2]
        float delta = cbrt(x_original * x_original) * cbrt(x_original * x_original) - 4 * x_original * x_original + 4;
        float y1 = (cbrt(x_original * x_original) + sqrt(delta)) / 2;
        float y2 = (cbrt(x_original * x_original) - sqrt(delta)) / 2;

        glVertex2f(x, y1);
        glVertex2f(x, y2);
    }
    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowPosition(400, 40);
    glutInitWindowSize(400, 400);
    glutCreateWindow("glHeart");

    gluOrtho2D(0, 1000, 1000, 0);


    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
