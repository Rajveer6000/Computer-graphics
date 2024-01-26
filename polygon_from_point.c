// #include <windows.h> // For MS Windows
#include <GL/glu.h>
#include <GL/glut.h> // GLUT, includes glu.h and gl.h
#include <GL/gl.h>
/* Handler for window-repaint event. Call back when the window first
appears and whenever the
window needs to be re-painted. */
void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, -0.5);
    glEnd();
    glFlush();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv); // Initialize GLUT
    // glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB);//set the display mode
    glutCreateWindow("RAJVEER CHOUDHARY"); // Create a window with thegiven title
    glutInitWindowSize(600, 640);          // Set the window's initial width &height
    glutInitWindowPosition(50, 50);        // Position the window's initial topleft corner
    glutDisplayFunc(Display);              // Register display callback handler forwindow re-paint
    glutMainLoop();                        // Enter the infinitely event-processing loop
    return 0;
}
