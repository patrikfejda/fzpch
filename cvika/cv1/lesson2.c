#include <GL/gl.h>
#include <GL/glu.h> // GL Utilities; toto potrebujeme az teraz.
#include <GL/glut.h>
void kresliTrojuh2D ()
{
glClear ( GL_COLOR_BUFFER_BIT );
glColor3f (0.0 , 0.0 , 1.0);
// Nastavme nasej 2-rozmernej OpenGL scene suradnice z intervalov
// -2 < x < 2, -1 < y < 1 .
gluOrtho2D ( -2.0 , 2.0 , -1.0 , 1.0); // funkcia z GL utilities
// Dala by sa nahradit zakladnou OpenGL funkciou
// glOrtho(-2.0, 2.0, -1.0, 1.0, -1.0, 1.0);
glBegin ( GL_TRIANGLES );
glVertex2f ( -0.8 , -0.8);
glVertex2f ( 0.8 , -0.8);
glVertex2f ( 0, 0.8);
glEnd ();
glutSwapBuffers (); // Vykresli pripravenu scenu.
}
int main (int argc , char ** argv )
{
glutInit (& argc , argv );
// glutInitDisplayMode(GLUT_RGBA); // nie je nutne pisat
glutInitDisplayMode ( GLUT_DOUBLE );
glutInitWindowSize (640 , 640); // zvolme nateraz stvorcove
glutInitWindowPosition (200 , 150);
glutCreateWindow (" OpenGL : trojuholnik ");
glutDisplayFunc (kresliTrojuh2D);
glClearColor (0.8 , 0.3 , 0.3 , 0.3);
glutMainLoop ();
return 0;
}

// gcc lesson2.c -lglut -lGL -lGLEW -lGLU -o main ; ./main
