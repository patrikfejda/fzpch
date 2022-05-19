#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h> // odkomentovat , ak chceme pouzivat printf()
//====================================================================
// icaskrok je v milisekundach. Kazdych 25 ms sa teda bude volat toto:
// kresliTrojuh2D()
// aktualizuj()
// Je to potrebne , lebo objekty na scene sa mohli pohnut a my chceme
// tieto zmeny co najplynulejsie zobrazovat.
//====================================================================
const int icaskrok = 25;
const float Lmax = 20.0; // rozmer sceny v smere X
float posunX = 0.0; // zaciatocna hodnota posuvu (uvazujme len v smere X)
void aktualizuj (const int ihod )
{
printf (" aktualizuj (): ihod = %d\n", ihod );
posunX += 0.05;
glutPostRedisplay (); // Tymto podavame ziadost o prekreslenie sceny.
// Je v zasade jedno , co je poslednym argumentom nasledujucej funkcie.
glutTimerFunc ( icaskrok , aktualizuj , ihod +1);
}
void obsluhaResize (int sirka , int vyska )
{
printf (" obsluhaResize (): sirka = %d px , vyska = %d px\n",sirka , vyska );
glViewport (0, 0, sirka , vyska );
glMatrixMode ( GL_PROJECTION );
//--------------------------------------------------------------
// Ak posuvame bod po bode (menej vhodny sposob),
// tak glLoadIdentity() musi byt tu, a nie v kresliTrojuh2D().
//--------------------------------------------------------------
glLoadIdentity ();
if ( sirka == 0) sirka ++;
const float pomstr = ((float) vyska )/ sirka ;
gluOrtho2D ( -0.5* Lmax , 0.5* Lmax , -0.5* Lmax * pomstr , 0.5* Lmax * pomstr );
}
void kresliTrojuh2D ()
{
printf (" kresliTrojuh2D (): Pripravujem kresbu .\n");
glClear ( GL_COLOR_BUFFER_BIT );
glColor3f (0.0 , 0.0 , 1.0);
glMatrixMode ( GL_MODELVIEW ); // nie je nutne to volat ,
// lebo GL_MODELVIEW je default.
glBegin ( GL_TRIANGLES );
glVertex2f ( -0.8+ posunX , -0.8);
glVertex2f ( 0.8+ posunX , -0.8);
glVertex2f ( 0.0+ posunX , 0.8);
glEnd ();
glutSwapBuffers ();
}
int main (int argc , char ** argv )
{
glutInit (& argc , argv );
// glutInitDisplayMode(GLUT_RGBA); // nie je nutne pisat
glutInitDisplayMode ( GLUT_DOUBLE );
glutInitWindowSize (1080 , 640);
glutInitWindowPosition (200 , 150);
glutCreateWindow (" OpenGL : trojuholnik ");
glutDisplayFunc ( kresliTrojuh2D ); // "callback" procedura na kreslenie
glClearColor (0.8 , 0.3 , 0.3 , 0.3); // definuje farbu vyplne okna
glutReshapeFunc ( obsluhaResize );
// aktualizuj() je "callback" funkcia kvoli zmenam v case.
// 0 je nami zvolena zaciatocna hodnota ihod.
glutTimerFunc ( icaskrok , aktualizuj , 0);
glutMainLoop ();
return 0;
}

// gcc lesson4.c -lglut -lGL -lGLEW -lGLU -o main ; ./main
