
/*


KOMPILOVAT A PUSTAT PRIKAZOM:

rm main ; rm out.csv ; clear ; gcc move_circle.c -lm -lglut -lGL -lGLEW -lGLU -o main ; ./main >> out.csv

*/



#include <GL/freeglut.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>

#define TX 0.02
#define TY 0.02
#define TZ 1

#define RADIUS 0.5
#define NUMOFRAYS 365
#define PI 3.14159265359

const float Lmax = 100.0;

const float mat[] = {TX,0,0,0,0,TY,0,0,0,0,TZ,0,0,0,0,1};
float move_x_red = 0;
float move_y_red = 0;
const int i_time_step = 25;

float sx = 0;
float sx0 = -50;
float sy = 0;
float sy0 = -50;
float vx, vy, v;
float g = 9.80665; // m/s^2

/////////////
/////////////
/////////////
float alfa = 0.4*PI;
float v0 = 30;
float h0 = 42; // 0 - 100
/////////////
/////////////
/////////////



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
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1, 1, 1);
    glVertex2f(sx+sx0, sy+sy0);
    float alphai, xn, yn;
    for (int i = 0; i <= NUMOFRAYS; i++)
    {
        alphai = ((float)i/NUMOFRAYS)*2*PI;
        xn = RADIUS * sin(alphai)+sx0;
        yn = RADIUS * cos(alphai)+sy0;
        glVertex2f(sx+xn, sy+yn);
    }
    if (sy < 0) {
        exit(0);
    }
    glEnd();
    glutSwapBuffers(); // Required to copy color buffer onto the screen.
}


void actualise(const int ihod) {
    float t = (float)ihod / (float)i_time_step;
    sx = v0 * t * cos(alfa);
    sy = h0 + v0 * t * sin(alfa) - 0.5 * g * t * t;
    vx = v0 * cos(alfa);
    vy = v0 * sin(alfa) - g * t;
    v = sqrt((vx*vx)+(vy*vy));
    printf("%f;%f;%f;%f;%f;%f\n", t, sx, sy, vx, vy, v);
    glutPostRedisplay();
    glutTimerFunc(i_time_step, actualise, ihod+1);
}


int main(int argc, char** argv)
{
    printf("t;xsur;ysur;vx;vy;v\n");
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
