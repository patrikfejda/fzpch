#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
// Ako elegantne tie nazvy hlavickovych suborov na seba nadvazuju! :-)
//#include <stdio.h> // odkomentovat pri pouziti printf
const float Lmax = 4.0; // rozmer sceny v smere X
void obsluhaResize (int sirka , int vyska )
{
//----------------------------------------------------------------
// Nazorna predstava je, ze OpenGL ,ceruzka' kresli na sklo
// (to je ten Viewport) umiestnene tesne za nepriehladnou doskou.
// V doske je vyrezane okno so sirkou a vyskou v pixeloch.
// Ak chceme , aby bolo ,sklo' (a na nom kresleny obraz) vidiet ,
// treba sklo (viewport) umiestnit presne tam, kde je okno v doske
// (inak by sklo, alebo jeho cast, bolo doskou zaclonene).
// Zvycajne najvhodnejsie je, ked ma to sklo presne taku velkost ,
// aku ma okno v doske.
// 0, 0, sirka , vyska su v pixeloch.
// Tie 0, 0 su posun ,skla' voci oknu v doske.
//
// Farba vyplne okna je, ak sa nemylim , viazana na okno,
// nie na ,sklo'.
//----------------------------------------------------------------
glViewport (0, 0, sirka , vyska );
//printf("sirka = %d\n", sirka);
//-----------------------------------------------------------------
// glMatrixMode s volbou GL_PROJECTION nastavi , ze operacie
// glLoadIdentity a gluOrtho2D robene nizsie sa budu tykat
// (nam neviditelnej) matice zabezpecujucej projekciu sceny
// (prepocet suradnic vsetkych objektov na scene do zobrazitelnych
// rozsahov , t. j. do rozsahov <-1, 1>).
//-----------------------------------------------------------------
glMatrixMode ( GL_PROJECTION );
glLoadIdentity (); // Prave TATO FUNKCIA zabezpeci , ze sa velkost troj-
// uholnika nebude pri prekresleni sceny scvrkavat.
//----------------------------------------------------------------------
// Pomocou gluOrtho2D() definujeme , KTORA CAST PRIESTORU (,fyzickeho'
// sveta , tu vlastne len ,fyzickej' plochy) SA BUDE ZOBRAZOVAT (kolmou
// projekciou). Ak chceme , aby mal obraz prirodzeny pomer vysky ku
// sirke , musime pomer stran zobrazovanej plochy nastavit zhodny
// s pomerom stran ,skla'.
// Funkcii gluOrtho2D() treba rozumiet tak, ze definuje ten vysek
// z ,fyzickeho' sveta , ktory chceme pomocou OpenGL zobrazit na
// viewport (t. j. na ,sklo') a nasledne aj do okna.
//
// gluOrtho2D robi svoju pracu tak, ze preskaluje suradnice sceny z nami
// definovanych rozsahov do rozsahov <-1, 1>. Robi to pomocou maticoveho
// nasobenia. gluOrtho2D by sa teda dala nahradit priamym vytvorenim
// vhodnej matice napr. pomocou glLoadMatrixf.
//----------------------------------------------------------------------
if ( sirka == 0) sirka ++;
const float pomstr = ((float) vyska )/ sirka ;
gluOrtho2D ( -0.5* Lmax , 0.5* Lmax , -0.5* Lmax * pomstr , 0.5* Lmax * pomstr );
}
void kresliTrojuh2D ()
{
glClear ( GL_COLOR_BUFFER_BIT );
glColor3f (0.0 , 0.0 , 1.0);
// V tejto procedure sa teda gluOrtho2D() NEMA POUZIVAT.
// Ma byt v obsluhaResize(), kam sme to presunuli.
glBegin ( GL_TRIANGLES );
glVertex2f ( -0.8 , -0.8);
glVertex2f ( 0.8 , -0.8);
glVertex2f ( 0, 0.8);
//----------------------------------------------------------
// Aj takyto vacsi by sa tentoraz uz zmestil na scenu , aspon
// ak prilis neznizime vysku okna (a ,skla ').
// Vhodnejsie by bolo vyjadrit suradnice tych vrcholov
// ako nasobky Lmax.
//----------------------------------------------------------
// glVertex2f(-1.3, -1.3);
// glVertex2f( 1.3, -1.3);
// glVertex2f( 0, 1.0);
glEnd ();
glutSwapBuffers ();
}
int main (int argc , char ** argv )
{
glutInit (& argc , argv );
// glutInitDisplayMode(GLUT_RGBA); // nie je nutne pisat
glutInitDisplayMode ( GLUT_DOUBLE );
//------------------------------------------------------------------
// Prikazom glutInitWindowSize() akoby vytvorime v nejakej
// NEPRIEHLADNEJ nekonecne rozlahlej doske obdlznikovy otvor - okno,
// cez ktore budeme vidiet na svet za doskou. Na obrazovke budeme
// vidiet len to, co nam umozni ten ,vypileny' otvor.
// Vyssie je tato predstava rozvita dalej.
//------------------------------------------------------------------
glutInitWindowSize (640 , 640); // zvolme nateraz stvorcove okno
glutInitWindowPosition (200 , 150);
glutCreateWindow (" OpenGL : trojuholnik ");
glutDisplayFunc ( kresliTrojuh2D );
glClearColor (0.8 , 0.3 , 0.3 , 0.3);
// Zavedieme ,callback' funkciu obsluhaResize().
glutReshapeFunc ( obsluhaResize );
glutMainLoop ();
return 0;
}

// gcc lesson3.c -lglut -lGL -lGLEW -lGLU -o main ; ./main
