#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

// Global Variables
GLfloat color[3];
GLfloat boundary_color[3] = {0.0, 0.0, 0.0};
GLfloat bcg_color[3] = {1.0, 1.0, 1.0};
GLfloat eye_color[3] = {0.0, 0.0, 1.0};
GLfloat nose_color[3] = {1.0, 1.0, 0.0};
GLfloat face_color[3] = {0.0, 1.0, 0.0};
GLfloat mouth_color[3] = {1.0, 0.0, 0.0};

float canvas_height = 600.0;
float canvas_width = 600.0;

float face_len = 300.0;
float face_x = 150.0;
float face_y = 150.0;

float eye_radius = 20.0;
float left_eye_center[2] = {230.0, 370.0};
float right_eye_center[2] = {370.0, 370.0};

float mouth_len = 100.0;
float mouth_brth = 50.0;
float mouth_x = 250.0;
float mouth_y = 190.0;

int colorsEqual(GLfloat color1[3], GLfloat color2[3])
{
    return (color1[0] == color2[0] &&
            color1[1] == color2[1] &&
            color1[2] == color2[2]);
}

void boundaryFill(int x, int y, float *fc, float *bc)
{

    glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, color);
    // printf(" (%d, %d) ==>  %f %f %f\n", x, y, color[0], color[1], color[2]);

    if (!colorsEqual(color, bc) && !colorsEqual(color, fc))
    {
        glColor3fv(fc);
        glPointSize(2.0);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();

        // Define the 8 neighboring pixels
        // int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
        // int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};
        int dx[] = {2, 2, 0, -2, -2, -2, 0, 2};
        int dy[] = {0, 2, 2, 2, 0, -2, -2, -2};
        // int dx[] = {6, 6, 0, -6, -6, -6, 0, 6};
        // int dy[] = {0, 6, 6, 6, 0, -6, -6, -6};

        for (int i = 0; i < 8; i++)
        {
            boundaryFill(x + dx[i], y + dy[i], fc, bc);
        }
    }

    return;
}

void bressenham_algo(float x1, float y1, float x2, float y2)
{

    float dx = abs(x2 - x1);
    float dy = abs(y2 - y1);

    int x_dir = (x1 < x2) ? 1 : -1;
    int y_dir = (y1 < y2) ? 1 : -1;

    float x = x1;
    float y = y1;

    if (dx == 0)
    {
        for (size_t i = 0; i < dy; i++)
        {
            y += y_dir;
            glVertex2f(x, y);
        }
    }

    else if (dy == 0)
    {
        for (size_t i = 0; i < dx; i++)
        {
            x += x_dir;
            glVertex2f(x, y);
        }
    }

    // Move along the x-axis
    else if (dx >= dy)
    {
        float pk = 2 * dy - dx;

        for (int i = 0; i < dx; i++)
        {
            glVertex2f(x, y);

            if (pk < 0)
            {
                pk += 2 * dy;
            }
            else
            {
                pk += 2 * (dy - dx);
                y += y_dir;
            }
            x += x_dir;
        }
    }

    // Move along the y-axis
    else
    {
        float pk = 2 * dx - dy;

        for (int i = 0; i < dy; i++)
        {
            glVertex2f(x, y);

            // Update pk
            if (pk < 0)
            {
                pk += 2 * dx;
            }
            else
            {
                pk += 2 * (dx - dy);
                x += x_dir;
            }
            y += y_dir;
        }
    }
}

void midPointCircle(float *center, float r)
{
    float x = r;
    float y = 0.0;
    float p = 1 - r;

    while (x >= y)
    {
        // printf("\n( %1.f, %1.f )", x, y);
        glVertex2f(x + center[0], y + center[1]);
        glVertex2f(y + center[0], x + center[1]);
        glVertex2f(-x + center[0], y + center[1]);
        glVertex2f(-y + center[0], x + center[1]);
        glVertex2f(-x + center[0], -y + center[1]);
        glVertex2f(-y + center[0], -x + center[1]);
        glVertex2f(x + center[0], -y + center[1]);
        glVertex2f(y + center[0], -x + center[1]);

        if (p < 0)
        {
            y++;
            p = p + 2 * y + 1;
        }
        else
        {
            x--;
            y++;
            p = p + 2 * y + 1 - 2 * x;
        }
    }
}

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, canvas_width, 0, canvas_height);
}

void display()
{
    printf("Displaying\n");
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3fv(boundary_color);
    glPointSize(3.0);
    glBegin(GL_POINTS);

    glVertex2f(0.0, 0.0);

    // Square [Face]
    bressenham_algo(face_x, face_y, face_x + face_len, face_y);                       // bottom line
    bressenham_algo(face_x + face_len, face_y, face_x + face_len, face_y + face_len); // right line
    bressenham_algo(face_x + face_len, face_y + face_len, face_x, face_y + face_len); // top line
    bressenham_algo(face_x, face_y + face_len, face_x, face_y);                       // left line

    // Triangle [Nose]
    bressenham_algo(280.0, 280.0, 320.0, 280.0); // bottom line
    bressenham_algo(280.0, 280.0, 300.0, 320.0); // left line
    bressenham_algo(300.0, 320.0, 320.0, 280.0); // right line

    // Rectangle [Mouth]
    bressenham_algo(mouth_x, mouth_y, mouth_x + mouth_len, mouth_y);                           // bottom line
    bressenham_algo(mouth_x + mouth_len, mouth_y, mouth_x + mouth_len, mouth_y + mouth_brth);  // right line
    bressenham_algo(mouth_x + mouth_len, mouth_y + mouth_brth, mouth_x, mouth_y + mouth_brth); // top line
    bressenham_algo(mouth_x, mouth_y + mouth_brth, mouth_x, mouth_y);                          // left line

    // Eyes [Circle]
    midPointCircle(left_eye_center, eye_radius);
    midPointCircle(right_eye_center, eye_radius);

    glEnd();

    glFlush();

    boundaryFill(left_eye_center[0], left_eye_center[1], eye_color, boundary_color);
    boundaryFill(right_eye_center[0], right_eye_center[1], eye_color, boundary_color);
    boundaryFill(mouth_x + 3, mouth_y + 3, mouth_color, boundary_color);
    boundaryFill(283, 283, nose_color, boundary_color);
    boundaryFill(face_x + 3, face_y + 3, face_color, boundary_color);

    return;
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(canvas_width, canvas_height);
    glutInitWindowPosition(700, 100);

    glutCreateWindow("Boundary Filling Algorithm");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
