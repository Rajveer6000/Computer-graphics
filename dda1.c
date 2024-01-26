#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
int step;
float x1, Y1, x2, y2;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    

    glVertex2f(0, 0);
    
    float x, y, m, dy, dx;
    x = x1;
    y = Y1;
    dx = x2 - x1;
    dy = y2 - Y1;
    m = dy / dx;
    step = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    glVertex2f(x, y);
    if (m > 1)
    {

        for (int i = 0; i < step; i++)
        {
            y++;
            x += (1 / m);
            printf("(%1.f , %1.f)\n", x, y);
            glVertex2f(x, y);
        }
    }

    else
    {

        for (int i = 0; i < step; i++)
        {
            x++;
            y += m;
            printf("(%1.f , %1.f)\n", x, y);
            glVertex2f(x, y);
        }
    }
    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 600);

    printf("Enter the value of co-ordenate x1 =: ");
    scanf("%f", &x1);
    printf("Enter the value of co-ordenate Y1 =: ");
    scanf("%f", &Y1);
    printf("Enter the value of co-ordenate x2 =: ");
    scanf("%f", &x2);
    printf("Enter the value of co-ordenate y2 =: ");
    scanf("%f", &y2);
   

    glutCreateWindow("hello");
    
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}