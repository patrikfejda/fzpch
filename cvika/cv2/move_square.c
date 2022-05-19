#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>

#define TX 0.5
#define TY 0.5
#define TZ 0

const float Lmax = 4.0;

const float mat[] = {1,0,0,0,0,1,0,0,0,0,1,0,TX,TY,TZ,1};
float move_x = 0;
float move_y = 0;
const int i_time_step = 25;

void rectangeResize(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // THESE TWO LINES DO THE SAME
    // glLoadMatrixf(mat);
    // glTranslatef(TX,TY,TZ);



    if (width == 0) width++;

    const float pomstr = ((float)height/width);
    gluOrtho2D(-0.5*Lmax, 0.5*Lmax, -0.5*Lmax*pomstr, 0.5*Lmax*pomstr);
}

void weird_triangle() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glColor3f(1, 1, 1);
        glVertex2f(0 + move_x, 0 + move_y);
        glVertex2f(-0.5 + move_x, 0.5 + move_y);
        glVertex2f(-1 + move_x, 0 + move_y);
        glVertex2f(-0.5 + move_x, -0.5 + move_y);
    glEnd();
    glutSwapBuffers(); // Required to copy color buffer onto the screen.
}

void actualise(const int ihod) {
    if (ihod%30 == 0) {
        move_x *= -1;
        move_y *= -1;
    }
    move_x += 0.03;
    move_y += 0.03;
    glutPostRedisplay();

    glutTimerFunc(i_time_step, actualise, ihod+1);

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
    glutTimerFunc(i_time_step, actualise, 0);
    glutMainLoop();
    return 0;
}

// rm main ; clear ; gcc move_square.c -lglut -lGL -lGLEW -lGLU -o main ; ./main
