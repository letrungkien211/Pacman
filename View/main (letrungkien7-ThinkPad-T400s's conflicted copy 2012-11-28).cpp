#include "view.hpp"
#include <GL/glut.h>
#include <cassert>

// Global variables
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 500

State state;
MinimaxAgent minimax;
vector<vector<Action> > combinedAction;
Action pacmanAction;


// Functions prototype
void Display();
void HandleKeyPress(unsigned char key, int x, int y);
void MyInit();
void InitGL();
void GameDraw();

void MyInit(){
    InitGL();
    state.Initialize(9,18,initWall, initFood);
    vector<double> coeff(NUMFEATURES);
    coeff[0] = 10;
    coeff[1] = 3;
    coeff[2] = -1;
    coeff[3] = -1;
    coeff[4] = 1000;
    minimax.SetCoeff(coeff);
    minimax.PreCalculateMinDistance(&state);
}

void InitGL(){
    glClearColor(1.0,1.0,0,1);
}

void Display(){
    glClear ( GL_COLOR_BUFFER_BIT );
    glClear (GL_DEPTH_BUFFER_BIT);
    // Where to add the game draw
    cout << state_ <<endl;
    glLoadIdentity();
    glPushMatrix();
    gameDraw();
    glColor3d(1,0,0);
    glutSolidTeapot(40.0);
    glPopMatrix();

}

void GLWidget::resizeGL(int width, int height){
    int side = qMin(width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho2d(0, width, 0, height);
    glMatrixMode(GL_MODELVIEW);
}



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
