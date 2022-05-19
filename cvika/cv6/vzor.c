/*


KOMPILOVAT A PUSTAT PRIKAZOM:

rm main ; rm out.csv ; clear ; gcc vzor.c -lm -lglut -lGL -lGLEW -lGLU -o main ; ./main

*/

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

const float Lmax = 5.0;

void obsluhaResize(int sirka, int vyska)
{
        glViewport(0, 0, sirka, vyska);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
	if (sirka == 0) sirka++;
	const float pomstr = ((float)vyska)/sirka;
	// doplniť
	glOrtho(-0.5*Lmax, 0.5*Lmax, -0.5*Lmax*pomstr, 0.5*Lmax*pomstr, 0, 10);
}

void kresliRovnobezky3D()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	// os x
	glBegin(GL_LINES);
        // red - x
        glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0, 0, 0);
		glVertex3f(Lmax, 0, 0);
        // green - y
        glColor3f(0.0, 0.9, 0.0);
        glVertex3f(0, 0, 0);
		glVertex3f(0, Lmax, 0);
        // blue - z
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0, 0, 0);
		glVertex3f(0, 0, Lmax);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);

	// doplniť
	glBegin(GL_LINES);
		// left
        glVertex3f(1, 1, 0);
		glVertex3f(1, 2, -1);
		// right
        glVertex3f(2, 1, 0);
		glVertex3f(2, 2, -1);
	glEnd();
	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("OpenGL: rovnobezky");
	glutDisplayFunc(kresliRovnobezky3D);
	glutReshapeFunc(obsluhaResize);
	glClearColor(1.0, 1.0, 1.0, 0);
	glutMainLoop();
	return 0;
}