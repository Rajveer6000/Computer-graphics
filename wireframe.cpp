#include <GL/glut.h>
#include <math.h>
#define PI 3.1416
void setPixel(GLint, GLint);
void ellipse(GLint, GLint, GLint, GLint, GLfloat);
void display();
void display()
{
        glClearColor(1,1,1, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,0);
    glPointSize(1.0);
    GLint xc = 0;
    GLint yc = 0;
    GLint r = 200;
    GLint ry = 50;
    GLint rx = 100;
    GLint d = 0;
 
    for (GLint theta = 1; theta <= 360; theta++)
        for (GLint d = 200; d > 0; d = d - 10)
        {
            ellipse(xc,d,200,100, theta);
            // ellipse(xc, d, ry, rx, theta);
        }
    for (GLint theta = 1; theta <= 360; theta++)
        for (GLint rx = 100; rx <= 0; rx++)
        {
            ellipse(xc, d, ry, rx, theta);
        }
    glFlush();
}
void ellipse(GLint xc, GLint yc, GLint rx, GLint ry, GLfloat theta)
{
    GLint x = xc + rx * cos(theta * PI / 180.0);
    GLint y = yc + ry * sin(theta * PI / 180.0);
    setPixel(x, y);
}
void setPixel(GLint xCoordinate, GLint yCoordinate)
{
    glBegin(GL_POINTS);
    glVertex2i(xCoordinate, yCoordinate);
    glEnd();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Wire Frame Model of Globe");
    gluOrtho2D(-500, 500, -500, 500);
    glutDisplayFunc(display);
    glutMainLoop();
}