#include "view.hpp"
#include <GL/glut.h>
#include <cassert>

View::View(const WindowSize &winsize){
    this->winsize = winsize;
}


class Vector3d{
public:
    double x, y , z;

    Vector3d(double x, double y, double z){
	this->x = x; 
	this->y = y;
	this->z = z;
    }
    double operator[](int i) const{
	assert(i>=0 && i<3);
	switch(i){
	case 0: return x;
	case 1: return y;
	case 2: return z;
	}
    }
    double &operator[](int i){
	assert(i>=0 && i<3);
	switch(i){
	case 0: return x;
	case 1: return y;
	case 2: return z;
	}

    }
};

class Rectangle{
public:
    int left, right , top, bottom;
    Rectangle(){
	left = right = top = bottom = 0;
    }
    Rectangle(int left, int right , int top, int bottom){
	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;
    }
    void Draw(const Vector3d &color){
	glBegin(GL_QUADS);
	glColor3d(color[0], color[1], color[2]);
	glVertex3d(left, top, 0);
	glVertex3d(right, top, 0);
	glVertex3f(right, bottom, 0);
	glVertex3f(left, bottom, 0);
	glEnd();
    }
};

void View::Draw(const Game&game){
    int rows = game.Rows();
    int cols = game.Cols();
    WindowSize blockSize(winsize.width/cols, winsize.height/rows);
    int blockSpacing = 1;
    
    // Draw Border
    glBegin(GL_LINE_LOOP);
    glColor3f(0.5,0.2,0.1);
    glVertex3f(0,0,0);
    glVertex3f(winsize.width-blockSize.width/2,0,0);
    glVertex3f(winsize.width-blockSize.height/2,winsize.height,0);
    glVertex3f(0,winsize.height,0);
    glEnd();

    // Draw Game
    for(int i = 0; i<rows; i++){
	for(int j = 0; j< cols; j++){
	    if(game(i,j).IsWall()){
		Rectangle rect;
		rect.left = j*(blockSize.width+blockSpacing)-blockSpacing;
		rect.right = rect.left + blockSize.width;
		rect.bottom = i*(blockSize.height+blockSpacing)- blockSpacing;
		rect.top = rect.bottom + blockSize.height;
		rect.Draw(Vector3d(1,0,0));
	    }
	    else if(game(i,j).IsFood()){
		
	    }
	}
    }
}


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
