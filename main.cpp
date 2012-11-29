#include "minimaxAgent.hpp"
#include <GL/glut.h>
#include <cassert>

int initFood[] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		 0,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,
		 0,1,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,1,0,
		 0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,
		 0,1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,0,
		 0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,
		 0,1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,0,
		 0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,
		 0,1,0,0,1,0,1,0,0,0,0,0,0,1,0,1,0,0,1,0,
		 0,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,
		 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		 
bool initWall[] ={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		  1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1, // 0
		  1,0,1,1,0,1,0,1,1,1,1,1,1,0,1,0,1,1,0,1 , // 1
		  1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1 ,
		  1,0,1,0,1,1,0,1,1,0,0,1,1,0,1,1,0,1,0,1 ,
		  1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1 ,
		  1,0,1,0,1,1,0,1,1,1,1,1,1,0,1,1,0,1,0,1 ,
		  1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1 ,
		  1,0,1,1,0,1,0,1,1,1,1,1,1,0,1,0,1,1,0,1 ,
		  1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,
		  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};


// Global variables
int  winWidth = 500;
int  winHeight = 250;
State state;
MinimaxAgent minimax;
vector<vector<Action> > combinedAction;
Action pacmanAction;


// Functions prototype
void Display();
void HandleKeyPress(unsigned int key, int x, int y);
void HandleSpecialKeyPress(unsigned char key, int x, int y);
void MyInit(int argc, char*argv[]);
void InitGL();

void MyInit(int argc, char*argv[]){
    state.Initialize(11,20,initWall, initFood);
    vector<double> coeff(NUMFEATURES);
    coeff[0] = atoi(argv[1]);
    coeff[1] = 0;
    coeff[2] = 0;
    coeff[3] = atoi(argv[2]);
    coeff[4] = INFINITY/2;
    coeff[5] = 0;
    coeff[6] = 0;
    minimax.SetCoeff(coeff);
    minimax.PreCalculateMinDistance(&state);
    InitGL();
}

void InitGL(){
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0,1.0,1.0,1.0);

}

void Display(){
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    // Where to add the game draw
    cout << state <<endl;

    glPushMatrix();
    int min = std::min(winHeight, winWidth);
    glScalef(min/15,-min/15,1);
    GameDraw(state);
    glPopMatrix();
    glutSwapBuffers();
}

void Reshape(int width, int height){
    glViewport(0,0,width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-width/2, width/2, -height/2, height/2);
    glMatrixMode(GL_MODELVIEW);
    cout << "Done resize" <<endl;
    winWidth = width;
    winHeight = height;
}

void HandleKeyPress(unsigned char key, int x, int y){
    switch(key){
    case 27:
	exit(-1);
	break;
    default:
	break;
    }
}

void HandleSpecialKeyPress(int key, int x, int y){
    if(state.IsFinal()!=UNKOWN)
	return;
    bool valid = true; 
    switch(key){
    case GLUT_KEY_UP:
	pacmanAction = UP; break;
    case GLUT_KEY_DOWN:
	pacmanAction = DOWN; break;
    case GLUT_KEY_RIGHT:
	pacmanAction = RIGHT; break;
    case GLUT_KEY_LEFT:
	pacmanAction = LEFT; break;
    case GLUT_KEY_HOME:
	pacmanAction = STOP; break;
    case GLUT_KEY_END:
	exit(-1); break;
    default:
	cout << "Invalid key!" <<endl;
	valid = false;
	break;
    }
    if(valid && state.IsLegalPacmanAction(pacmanAction)){
	vector<Action> combinedAction = minimax.ChooseCombinedGhostAction(state, 9);
    	state.GetNextState(pacmanAction, combinedAction);
    	cout << "Ghost Minimax Move: " << combinedAction<< endl;
	glutPostRedisplay();
    }
    else{
	cout << "Ilegal Pacman Move!" <<endl;
    }
}

void GameDraw(){
    if(state.IsFinal()==UNKOWN){
	cout << state <<endl;
    }
    else{
	cout << "Pacman: " << state.IsFinal() <<endl;
    }
}

int main(int argc, char **argv) {
    glutInit               ( &argc, argv );
    glutInitDisplayMode    ( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize     ( winWidth+100, winHeight+100 );    
    glutInitWindowPosition ( 50, 50 ); 
    glutCreateWindow       ( "Minimax Ghost" );

    MyInit (argc, argv);  // initialization

    glutDisplayFunc ( Display );  // display
    glutSpecialFunc(HandleSpecialKeyPress);
    glutKeyboardFunc(HandleKeyPress);
    glutReshapeFunc(Reshape);
    glutMainLoop ( );
}
