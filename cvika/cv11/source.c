/**
rm main ; gcc source.c -lm -lglut -lGL -lGLEW -lGLU -o main ; ./main
**/

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#include <math.h>
#include <float.h>
#define _USE_MATH_DEFINES
#define PI 3.14

#define CBALL 2
#define DIMS 2

float dt = 0.01;
float dt_new;
float g = 9.80665;
float t = 0;
float v0_1;
float v0_2;
float h0;
float ymax;
float xmax;
float r = 8;
int diamater = 5;
int num_of_balls = 2;
float sur[2][2];
float v[2][2];
float colors[2][3] = { {1.0,0.2,0.2},{0.2,1.0,0.2} };
int size = 500;
int time_step = 10;
int hit = 0;
int first_i;
int first_j;
int n = 0;
double first_time;
bool will_be_ball = false;
float table_height;
float table_width;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.2, 0.2, 0.2);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRectf(-size / 2 + (size / 10), -size / 3 + (size / 10), size / 2 - (size / 10), size / 3 - (size / 10));

    for (int i = 0; i < 2; i++)
    {
        glLoadIdentity();
        glTranslatef(sur[i][0], sur[i][1], 0.0);
        glScalef(r, r, 0.0);

        glBegin(GL_TRIANGLE_FAN);
        glColor3f(colors[i][0], colors[i][1], colors[i][2]);
        glVertex2f(0.0, 0.0);
        for (float j = 0; j <= 360; j++)
            glVertex2f(cos((j * 2 * M_PI) / 360), sin((j * 2 * M_PI) / 360));
        glEnd();
    }

    glutSwapBuffers();
}


void resizeWindow(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (width == 0)
        width++;
    const float sideRatio = ((float)height / width);

    gluOrtho2D(-0.5 * size, 0.5 * size, -0.5 * size * sideRatio, 0.5 * size * sideRatio);
}


void computeNextHit()
{
    double sides[2] = { table_width, table_height };
    double min = DBL_MAX;
    double minCandidate = 0;

    for (int i = 0; i < CBALL; i++)
    {
        for (int j = 0; j < DIMS; j++)
        {
            if (v[i][j] < 0)
            {
                minCandidate = (sur[i][j] - (-1 * sides[j] + r)) / (-v[i][j]);
                if (minCandidate < min)
                {
                    min = minCandidate;
                    first_i = i;
                    first_j = j;
                }
            }
            else if (v[i][j] > 0)
            {
                minCandidate = ((sides[j] - (sur[i][j] + r))) / v[i][j];
                if (minCandidate < min)
                {
                    min = minCandidate;
                    first_i = i;
                    first_j = j;
                }
            }
            else
            {
                min = 1e-6;
            }
        }
    }

    double bij = 0.0, rijsq = 0.0, vijsq = 0.0;
    for (int i = 0; i < DIMS; i++)
    {
        bij += (sur[1][i] - sur[0][i]) * (v[1][i] - v[0][i]);
        rijsq += (sur[1][i] - sur[0][i]) * (sur[1][i] - sur[0][i]);
        vijsq += (v[1][i] - v[0][i]) * (v[1][i] - v[0][i]);
    }
    if (bij < 0.0 && bij * bij - vijsq * (rijsq - 4 * r * r) > 0.0)
    {
        double tij = (-bij - sqrt(bij * bij - (rijsq - 4 * r * r) * vijsq)) / vijsq;
        if (tij >= 0.0 && tij < min)
        {
            min = tij;
            will_be_ball = true;
        }
    }
    first_time = min;
}



void Update(const int ihod)
{
    if (ihod == 1) {
        computeNextHit();
        n = 1 + (int)(first_time / dt);
        dt_new = (first_time / n) < 1e-6 ? 1e-6 : first_time / n;
    }

    for (int i = 0; i < CBALL; i++) {
        for (int j = 0; j < DIMS; j++) {
            sur[i][j] += v[i][j] * dt_new;
        }
    }
    glutPostRedisplay();

    if (ihod == n) {
        double rx = sur[1][0] - sur[0][0];
        double ry = sur[1][1] - sur[0][1];
        double vx = v[1][0] - v[0][0];
        double vy = v[1][1] - v[0][1];

        double D = sqrt(rx * rx + ry * ry);

        double Ix = rx * (rx * vx + ry * vy) / (D * D);
        double Iy = ry * (rx * vx + ry * vy) / (D * D);

        if (!will_be_ball) {
            v[first_i][first_j] *= -1;
        }
        else if (will_be_ball) {
            if (D <= 2 * r) {
                v[0][0] += Ix;
                v[0][1] += Iy;
                v[1][0] += -Ix;
                v[1][1] += -Iy;

                will_be_ball = false;
            }
        }
        glutTimerFunc(time_step, Update, 1);
    }
    else {
        glutTimerFunc(time_step, Update, ihod + 1);
    }
}
int main(int argc, char* argv[])
{
    srand(time(0));

    // Starting surr for balls
    sur[0][0] = -50;
    sur[0][1] = 10;
    sur[1][0] = 50;
    sur[1][1] = 20;

    for (int i = 0; i < CBALL; i++) {
        // random alfa for every ball
        int alfa = rand() % 360;
        // random speed for every ball
        int v0 = 1050;
        v[i][0] = (v0 * cos(alfa * ((M_PI / 180))));
        v[i][1] = (v0 * sin(alfa * ((M_PI / 180))));
    }

    table_height = (float)(size / 3.0 - (size / 10.0));
    table_width = (float)(size / 2.0 - (size / 10.0));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Biliard");
    glutDisplayFunc(display);
    glutReshapeFunc(resizeWindow);
    glutTimerFunc(time_step, Update, 1);
    glutMainLoop();
    return 0;
}