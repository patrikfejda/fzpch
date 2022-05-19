#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>

const float Lmax = 4.0;

#define TX 0
#define TY 0
#define TZ 0
#define SX 0
#define SY 0
#define RADIUS 0.5
#define NUMOFRAYS 365
#define PI 3.14159265359
float mat[] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, TX, TY, TZ, 1};

void rectangeResize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // THESE TWO LINES DO THE SAME
    // glLoadMatrixf(mat);
    glTranslatef(TX, TY, TZ);

    if (width == 0)
        width++;

    const float pomstr = ((float)height / width);
    gluOrtho2D(-0.5 * Lmax, 0.5 * Lmax, -0.5 * Lmax * pomstr, 0.5 * Lmax * pomstr);
}

void weird_triangle()
{
    printf("ADASDSA\n");
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1, 1, 1);
    glVertex2f(SX, SY);
    float alphai, xn, yn;
    for (int i = 0; i <= NUMOFRAYS; i++)
    {
        alphai = ((float)i/NUMOFRAYS)*2*PI;
        xn = RADIUS * sin(alphai);
        yn = RADIUS * cos(alphai);
        printf("%f %f\n", xn, yn);
        glVertex2f(SX+xn, SY+yn);
    }
    glEnd();
    glutSwapBuffers(); // Required to copy color buffer onto the screen.
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Hello world :)");
    glutDisplayFunc(weird_triangle);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutReshapeFunc(rectangeResize);
    glutMainLoop();
    return 0;
}

// rm main ; clear ; gcc circle.c -lm -lglut -lGL -lGLEW -lGLU -o main ; ./main
