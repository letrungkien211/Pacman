#include "view.hpp"
#include <GL/glut.h>
#include <cassert>


void Display();
void HandleKeyPress(unsigned char key, int x, int y);
void Idle();
void Update(int arg);


int main(int argc, char **argv) {
    glutInit               ( &argc, argv );
    glutInitDisplayMode    ( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize     ( WINDOW_WIDTH+100, WINDOW_HEIGHT+100 );    
    glutInitWindowPosition ( 50, 50 ); 
    glutCreateWindow       ( "AI's Pacman & Ghost" );

    MyInit ( );  // initialization

    glutDisplayFunc ( Display );  // display
    glutKeyboardFunc(HandleKeyPress);  // keyboard 

    glutTimerFunc(100,Update,0);  // timer's function
    glutIdleFunc(Idle);
    glutMainLoop ( );
}
