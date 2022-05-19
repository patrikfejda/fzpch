#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>

#define TX 0.02
#define TY 0.02
#define TZ 1

const float Lmax = 100.0;

const float mat[] = {TX,0,0,0,0,TY,0,0,0,0,TZ,0,0,0,0,1};
float move_x_red = 0;
float move_y_red = 0;
float move_x_green = 0;
float move_y_green = 0;
const int i_time_step = 25;

void rectangeResize(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (width == 0) width++;

    const float pomstr = ((float)height/width);

    // the next two lines do the same:
    glLoadMatrixf(mat);
    // gluOrtho2D(-0.5*Lmax, 0.5*Lmax, -0.5*Lmax*pomstr, 0.5*Lmax*pomstr);
}

void print_square() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glColor3f(1, 0, 0);
        glVertex2f(-50 + move_x_red, 0 + move_y_red);
        glVertex2f(-50.5 + move_x_red, 0.5 + move_y_red);
        glVertex2f(-51 + move_x_red, 0 + move_y_red);
        glVertex2f(-50.5 + move_x_red, -0.5 + move_y_red);
    glEnd();
    glBegin(GL_QUADS);
        glColor3f(0, 1, 0);
        glVertex2f(0 + move_x_green, 0 + move_y_green);
        glVertex2f(-0.5 + move_x_green, 0.5 + move_y_green);
        glVertex2f(-1 + move_x_green, 0 + move_y_green);
        glVertex2f(-0.5 + move_x_green, -0.5 + move_y_green);
    glEnd();
    glutSwapBuffers(); // Required to copy color buffer onto the screen.
}

void print_square_green() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glColor3f(0, 1, 0);
        glVertex2f(0 + move_x_red, 0 + move_y_red);
        glVertex2f(0.5 + move_x_red, -0.5 + move_y_red);
        glVertex2f(1 + move_x_red, 0 + move_y_red);
        glVertex2f(0.5 + move_x_red, 0.5 + move_y_red);
    glEnd();
    glutSwapBuffers(); // Required to copy color buffer onto the screen.
}


void actualise(const int ihod) {
    move_x_red += 0.25;
    move_x_green += 0.125;
    glutPostRedisplay();
    glutTimerFunc(i_time_step, actualise, ihod+1);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(1080,1080);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Hello world :)");
    glutDisplayFunc(print_square);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutReshapeFunc(rectangeResize);
    glutTimerFunc(i_time_step, actualise, 0);
    glutMainLoop();
    return 0;
}

// rm main ; clear ; gcc homework.c -lglut -lGL -lGLEW -lGLU -o main ; ./main



// VYPOCET:

// i_time_step = 25 ms = 0.025 seconds

// > every redrawn mean:
// red: +0,25 m (every 25 ms = 0.025 seconds)
// green: +0,125 m (every 25 ms = 0.025 seconds)

// > that means that the velocity is:
// red: 0,25 m / 0.025 seconds = 10 m/s = 36 km/h
// green: 0,125 m / 0.025 seconds = 5 m/s = 18 km/h

// > at start
// >>red>>.......(50m).......>>green>>.......(50m).......END

// It takes:
// - green: 10 second (50m/5ms) to get to the END
// - red: 10 second (100m/10ms) to get to the END


//
