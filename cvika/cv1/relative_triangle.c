#include <GL/freeglut.h>
#include <GL/gl.h>

// void renderFunction()
// {
//     glClearColor(0.0, 0.0, 0.0, 0.0);
//     glClear(GL_COLOR_BUFFER_BIT);
//     glColor3f(1.0, 1.0, 1.0);
//     glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
//     glBegin(GL_POLYGON);
//         glVertex2f(-0.5, -0.5);
//         glVertex2f(-0.5, 0.5);
//         glVertex2f(0.5, 0.5);
//         glVertex2f(0.5, -0.5);
//     glEnd();
//     glFlush();
// }

void red_screen() {
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

void relative_triangle() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
        glColor3f(1, 0, 0); // red
        glVertex2f(-0.8, -0.8);
        glVertex2f(0.8, -0.8);
        glVertex2f(0, 0.8);
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
    glutCreateWindow("Hello world");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutDisplayFunc(relative_triangle);
    glutMainLoop();
    return 0;
}

// gcc relative_triangle.c -lglut -lGL -lGLEW -lGLU -o main ; ./main
