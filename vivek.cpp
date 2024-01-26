#include <GL/glut.h>
#include <cmath>

void drawRangoli(int x, int y, int size) {
    if (size == 1) {
        glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x + 1, y);
        glVertex2f(x + 1, y + 1);
        glVertex2f(x, y + 1);
        glEnd();
        return;
    }

    int newSize = size / 2;

    for (int i = 0; i < 4; i++) {
        drawRangoli(x + newSize, y + newSize, newSize);
        glRotatef(90, 0, 0, 1);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawRangoli(-200, -200, 400);

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-500.0, 500.0, -500.0, 500.0);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Rangoli");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}