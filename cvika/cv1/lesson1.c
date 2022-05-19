#include <GL/gl.h>
#include <GL/glut.h>
void kresliTrojuh2D ()
{
glClear ( GL_COLOR_BUFFER_BIT ); // nastavi definovanu farbu pozadia okna
glColor3f (0.0 , 0.0 , 1.0); // definuje a nastavi farbu trojuholnika
//---------------------------------------------------------------------
// Pokial to nezariadime inak (a tu sme to naozaj nezariadili), tak na
// OpenGL scene sa budu dat zobrazit len suradnice z rozsahov <-1, 1>.
//---------------------------------------------------------------------
glBegin ( GL_TRIANGLES );
glVertex2f ( -0.8 , -0.8);
glVertex2f ( 0.8 , -0.8);
glVertex2f ( 0, 0.8);
// Tento vacsi by sa nezmestil na scenu:
// glVertex2f(-2.0, -2.0);
// glVertex2f( 2.0, -2.0);
// glVertex2f( 0, 2.0);
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
glutDisplayFunc ( kresliTrojuh2D );
glClearColor (0.8 , 0.3 , 0.3 , 0.3); // definuje farbu vyplne okna
// (teda farbu pozadia)
glutMainLoop ();
return 0;
}

// gcc lesson1.c -lglut -lGL -lGLEW -lGLU -o main ; ./main
