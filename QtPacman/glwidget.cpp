#include "glwidget.h"
#include <QtGui>
#include <GL/glut.h>
#include "state.hpp"
using namespace Qt;

int initFood[] ={10,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,
		 1,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,1,
		 1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
		 1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,
		 1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,
		 1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,
		 1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
		 1,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,1,
		 1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,10};
		 
bool initWall[] ={0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0, // 0
		  0,1,1,0,1,0,1,1,1,1,1,1,0,1,0,1,1,0,  // 1
		  0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0, 
		  0,1,0,1,1,0,1,1,0,0,1,1,0,1,1,0,1,0, 
		  0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0, // 5
		  0,1,0,1,1,0,1,1,1,1,1,1,0,1,1,0,1,0, 
		  0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0, 
		  0,1,1,0,1,0,1,1,1,1,1,1,0,1,0,1,1,0,  // 1
		  0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0};


GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
}

GLWidget::~GLWidget(){

}

void GLWidget::initializeGL(){
    glClearColor(1.0,1.0,0,1);
    gameInit();
}

int angle  = 40;
void GLWidget::paintGL(){
    glClear ( GL_COLOR_BUFFER_BIT );
    glClear (GL_DEPTH_BUFFER_BIT);
    // Where to add the game draw
    cout << state_ <<endl;
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 2, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glPushMatrix();
    glRotated(angle,1,1,0);
    glColor3d(1,0,0);
    gameDraw();
    glutSolidTeapot(40.0);
    glPopMatrix();
}
void GLWidget::resizeGL(int width, int height){
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width/2, width/2, -height/2, height/2, 1, 50);
    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::keyPressEvent(QKeyEvent *keyEvent){
    angle+=10;
    bool valid = true; 
    switch(keyEvent->key()){
    case Key_Up:    
	pacmanAction = UP; break;
    case Key_Down:  
	pacmanAction = DOWN; break;
    case Key_Right:
	pacmanAction = RIGHT; break;
    case Key_Left:
	pacmanAction = LEFT; break;
    case Key_Shift:
	pacmanAction = STOP; break;
    case Key_Escape:
	close(); break;
    default:
	cout << "Invalid key!" <<endl;
	valid = false;
	break;
    }
    if(valid && state_.IsLegalPacmanAction(pacmanAction)){

	vector<Action> combinedAction = minimax_.ChooseCombinedGhostAction(state_, 9);
    	state_.GetNextState(pacmanAction, combinedAction);
    	cout << "Ghost Minimax Move: " << combinedAction<< endl;
	keyEvent->accept();
	updateGL();
    }
    else{
	cout << "Ilegal Pacman Move!" <<endl;
		keyEvent->ignore();
    }
}


void GLWidget::gameInit(){
    state_.Initialize(9,18,initWall, initFood);
    vector<double> coeff(NUMFEATURES);
    coeff[0] = 10;
    coeff[1] = 3;
    coeff[2] = -1;
    coeff[3] = -1;
    coeff[4] = 1000;
    minimax_.SetCoeff(coeff);
    minimax_.PreCalculateMinDistance(&state_);
}
void GLWidget::gameDraw(){

}
void GLWidget::gameLoop(){

}
