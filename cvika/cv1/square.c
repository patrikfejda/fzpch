#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>

const float Lmax = 4.0;

void rectangeResize(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (width == 0) width++;

    const float pomstr = ((float)height/width);
    gluOrtho2D(-0.5*Lmax, 0.5*Lmax, -0.5*Lmax*pomstr, 0.5*Lmax*pomstr);
}

void weird_triangle() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glColor3f(1, 1, 1);
        glVertex2f(1, 0);
        glVertex2f(0, 1);
        glVertex2f(-1, 0);
        glVertex2f(0, -1);
    glEnd();
    glutSwapBuffers(); // Required to copy color buffer onto the screen.
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Hello world :)");
    glutDisplayFunc(weird_triangle);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutReshapeFunc(rectangeResize);
    glutMainLoop();
    return 0;
}

// gcc square.c -lglut -lGL -lGLEW -lGLU -o main ; ./main
