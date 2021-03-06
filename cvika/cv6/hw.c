
/*


KOMPILOVAT A PUSTAT PRIKAZOM:

rm main ; rm out.csv ; clear ; gcc hw.c -lm -lglut -lGL -lGLEW -lGLU -o main ; ./main 0.50 20 0 2 >> out.csv
rm main ; rm out.csv ; clear ; gcc hw.c -lm -lglut -lGL -lGLEW -lGLU -o main ; ./main 0.25 20 0 2 >> out.csv



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

#define NUMOFRAYS 365
#define PI 3.14159265359

const float mat[] = {TX,0,0,0,0,TY,0,0,0,0,TZ,0,0,0,0,1};
float move_x_red = 0;
float move_y_red = 0;
const int i_time_step = 25;
float ymax, xmax;

float step_count = 0;
float sx = 0;
float sx0 = 0;
float sy = 0;
float vx, vy, v;
float g = 9.80665; // m/s^2

int window_width, window_height;

/////////////
/////////////
/////////////
float alfa;
float v0 = 30;
float h0 = 0; // 0 - 100
float RADIUS = 0.5;
/////////////
/////////////
/////////////



void rectangeResize(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);

    if (width == 0) width++;

    const float pomstr = ((float)height/width);


    glOrtho(-2, xmax+2, -2, xmax*pomstr+2, -10, 10);

}

void print_square() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (sy < 0) {
        exit(0);
    }

	glMatrixMode(GL_MODELVIEW);

	// os x
	glBegin(GL_LINES);
        // red - x
        glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0, 0, 0);
		glVertex3f(xmax, 0, 0);
        // green - y
        glColor3f(0.0, 0.9, 0.0);
        glVertex3f(0, 0, 0);
		glVertex3f(0, xmax, 0);
        // blue - z
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0, 0, 0);
		glVertex3f(0, 0, xmax);
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
    step_count+=0.2;
	glTranslated(sx, sy, 0);
	glutWireSphere (RADIUS, 7, 6);
	glPopMatrix();

    glLoadIdentity();

    glutSwapBuffers(); // Required to copy color buffer onto the screen.
}


void actualise(const int ihod) {
    float t = (float)ihod / (float)i_time_step;
    sx = sx0 + v0 * t * cos(alfa);
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
    window_width = 1000;
    window_height = 1000;
    // use running from CLI with args
    if(argc == 5) {
        // printf("%s %f %f %f %f\n", argv[0], atof(argv[1]), atof(argv[2]), atof(argv[3]), atof(argv[4]));
        alfa = (atof(argv[1])*PI);
        v0 = atof(argv[2]);
        h0 = atof(argv[3]);
        RADIUS = atof(argv[4]);
        // printf("%f %f %f %f\n\n", alfa, v0, h0, RADIUS);
    }
    else {
        printf("INPUT SHOULD BE ./main <radians> <height> <velocity> <diameter>\n");
        return 0;
    }
    if (h0 < 0) {
        printf("INPUT SHOULD BE ./main <radians> <height> <velocity> <diameter>\n");
        printf("STOP: za??iato??n?? s??radnica mus?? by?? kladn??.\n");
        return 0;
    }
    if (alfa > 0.51*PI || alfa < -0.51*PI) {
        printf("INPUT SHOULD BE ./main <radians> <height> <velocity> <diameter>\n");
        printf("STOP:uhol mus?? by?? z intervalu <-0.5rad, 0.5rad>!\n");
        return 0;
    }

    xmax = (v0*v0*sin(2*alfa))/(g);
    // printf("%.10f\n",0.5*PI);
    // printf("%.10f\n",alfa);
    if (alfa >= 0.5*PI || alfa <= -0.5*PI) {
        xmax+=10;
        printf("KOLMY VRH\n");
        sx0 = 5;
    }
    ymax = h0 + (v0*v0*sin(alfa)*sin(alfa))/(2*g);
    window_width = xmax*30;
    window_height = ymax*30;
    while (window_width > 1000 || window_height > 1000) {
        window_width = window_width * 0.9;
        window_height = window_height * 0.9;
    }
    printf("XMAX: %f\n", xmax);
    printf("YMAX: %f\n", ymax);
    printf("t;xsur;ysur;vx;vy;v\n");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Hello world :)");
    glutDisplayFunc(print_square);
    glClearColor(0,0,0,0);
    glutReshapeFunc(rectangeResize);
    glutTimerFunc(i_time_step, actualise, 0);
    glutMainLoop();
    return 0;
}
