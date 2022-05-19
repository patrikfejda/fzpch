
/*


KOMPILOVAT A PUSTAT PRIKAZOM:

rm main ; rm out.csv ; clear ; gcc biliard.c -lm -lglut -lGL -lGLEW -lGLU -o main ; ./main 50 30 1 0.4 >> out.txt

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

#define RADIUS 1
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
float v0 = 1;
float h0 = 42; // 0 - 100
/////////////
/////////////
/////////////

int boom = 0;

#define DOWN_BORDER 21
#define UP_BORDER 79


void rectangeResize(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (width == 0) width++;

    const float pomstr = ((float)height/width);

    // the next two lines do the same:
    // glLoadMatrixf(mat);
    gluOrtho2D(-0.6*Lmax, 0.6*Lmax, -0.6*Lmax*pomstr, 0.6*Lmax*pomstr);
}

void print_square() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
        glColor3f(0.2, 0.2, 0.2);
        glVertex2f(30, 30);
        glVertex2f(-30, 30);
        glVertex2f(-30, -30);
        glVertex2f(30, -30);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1, 0, 0);
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
    sx += vx;
    sy += vy;
    // printf("%f %f\n", sx, sy);
    if (sx >= UP_BORDER || sx <= DOWN_BORDER) {
        vx = -vx;
        boom++;
        printf("%i %.2f %.2f %.2f\n", boom, t, atan(vx/vy)*180/PI, 2*vx);

    }

    if (sy >= UP_BORDER || sy <= DOWN_BORDER) {
        vy *= -1;
        boom++;
        printf("%i %.2f %.2f %.2f\n", boom, t, atan(vx/vy)*180/PI, 2*vy);
    }


    v = sqrt((vx*vx)+(vy*vy));
    glutPostRedisplay();
    glutTimerFunc(i_time_step, actualise, ihod+1);
}


int main(int argc, char** argv)
{

    // input
    if (argc != 5)
    {
        printf("wrong input - use <sx> <sy> <v0> <aplha>!\n");
        printf("aplha needs to be (0;1> !\n");
        exit(0);
    }
    if (atof(argv[3]) <= 0 || atof(argv[3]) > 1) {
        printf("aplha needs to be (0;1> !\n");
        exit(0);
    }

    if (atof(argv[1]) <= DOWN_BORDER || atof(argv[1]) >= UP_BORDER) {
        printf("sx and sy needs to be (%i;%i) !\n", DOWN_BORDER, UP_BORDER);
        exit(0);
    }

    if (atof(argv[2]) <= DOWN_BORDER || atof(argv[2]) >= UP_BORDER) {
        printf("sx and sy needs to be (%i;%i) !\n", DOWN_BORDER, UP_BORDER);
        exit(0);
    }
    sx = atof(argv[1]);
    sy = atof(argv[2]);
    v0 = atof(argv[3]);
    vx = v0;
    vy = v0*atof(argv[4]);

    printf("COUNTER TIME DEGREES DELTA_MOMENTUM \n");
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
