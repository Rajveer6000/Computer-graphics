#include <GL/glut.h>
#include <cmath>

// Function to draw a line
void drawLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
    
}

// Function to draw the Koch curve
void drawKoch(float x1, float y1, float x2, float y2, int iterations) {
    if (iterations == 0) {
        drawLine(x1, y1, x2, y2);
    } else {

        float deltaX = (x2 - x1) / 3.0;
        float deltaY = (y2 - y1) / 3.0;

        float xA = x1 + deltaX;
        float yA = y1 + deltaY;

        float xB = x1 + 2 * deltaX;
        float yB = y1 + 2 * deltaY;

        float xC = 0.5 * (x1 + x2) + sqrt(3) * (y1 - y2) / 6.0;
        float yC = 0.5 * (y1 + y2) + sqrt(3) * (x2 - x1) / 6.0;

        float xD = x2 - deltaX;
        float yD = y2 - deltaY;

        drawKoch(x1, y1, xA, yA, iterations - 1);
        drawKoch(xA, yA, xC, yC, iterations - 1);
        drawKoch(xC, yC, xB, yB, iterations - 1);
        drawKoch(xB, yB, xD, yD, iterations - 1);
        drawKoch(xD, yD, x2, y2, iterations - 1);
    }
}

// Function to handle all drawings
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // Set color to white

    // Change the parameters as needed
    float x1 = 100, y1 = 100.0;
    float x2 = 0, y2 = 0;
    int iterations = 2;

    drawKoch(x1, y1, x2, y2, iterations);
    glFlush();

}

// Initialize OpenGL
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Set background color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-300,300,-300,300); // Set the coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Koch Curve");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
