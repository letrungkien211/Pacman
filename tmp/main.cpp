#include "alphabetaAgent.hpp"
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/OpenGL.h>
#else
#include <GL/glut.h>
#endif

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
		  1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,
		  1,0,1,1,0,1,0,1,1,1,1,1,1,0,1,0,1,1,0,1,
		  1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
		  1,0,1,0,1,1,0,1,1,0,0,1,1,0,1,1,0,1,0,1,
		  1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,
		  1,0,1,0,1,1,0,1,1,1,1,1,1,0,1,1,0,1,0,1,
		  1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,
		  1,0,1,1,0,1,0,1,1,1,1,1,1,0,1,0,1,1,0,1,
		  1,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,
		  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

// Global variables
int  winWidth = 500;
int  winHeight = 250;
State state;
MinimaxAgent* agent;
vector<vector<Action> > combinedAction;
Action pacmanAction;
int depth;


// Functions prototype
void Display();
void HandleKeyPress(unsigned int key, int x, int y);
void HandleSpecialKeyPress(unsigned char key, int x, int y);
void MyInit(int argc, char*argv[]);
void InitGL();

void MyInit(int argc, char*argv[]){
    state.Initialize(11,20,initWall, initFood);
    vector<double> coeff(NUMFEATURES);
    if(argc > 1){
	if(argv[1][0]=='m')
	    agent = new MinimaxAgent();
	else if(argv[1][0]=='a')
	    agent = new AlphaBetaAgent();
	else{
	    cout << "Invalid option!" <<endl;
	    exit(-1);
	}
    }
    else{
	agent = new AlphaBetaAgent();
    }
    if(argc>2){
	depth = atoi(argv[2]);
    }
    else{
	depth = 12;
    }
	
    if(argc>5){
	coeff[0] = atoi(argv[3]);
	coeff[1] = atoi(argv[4]);
	coeff[2] = atoi(argv[5]);
    }
    else{
	coeff[0] = 10;
	coeff[1] = -5;
	coeff[2] = 5;
    }
    coeff[3] = 0;
    coeff[4] = 0;
    coeff[5] = 0;
    agent->SetCoeff(coeff);
    agent->PreCalculateMinDistance(&state);
    InitGL();
}

void InitGL(){
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0,1.0,1.0,1.0);
}

void Display(){
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
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
    case 'r':
	state.Initialize(11,20,initWall, initFood);
	glutPostRedisplay();
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
	pacmanAction = agent->ChoosePacmanAction(state, depth);
	break;
    default:
	cout << "Invalid key!" <<endl;
	valid = false;
	break;
    }
    if(valid && state.IsLegalPacmanAction(pacmanAction)){
	state.GetNextState(pacmanAction);
	vector<Action> combinedAction = agent->ChooseCombinedGhostAction(state, depth);
    	state.GetNextState(combinedAction);
    	cout << "Ghost Agent Move: " << combinedAction<< endl;
	glutPostRedisplay();
    }
    else{
	cout << "Ilegal Pacman Move!" <<endl;
    }
}

int main(int argc, char **argv) {
    glutInit               ( &argc, argv );
    glutInitDisplayMode    ( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize     ( winWidth+100, winHeight+100 );    
    glutInitWindowPosition ( 50, 50 ); 
    glutCreateWindow       ( "Pacman Game! Minimax+AlphaBetaPrunning" );

    MyInit (argc, argv);  // initialization

    glutDisplayFunc ( Display );  // display
    glutSpecialFunc(HandleSpecialKeyPress);
    glutKeyboardFunc(HandleKeyPress);
    glutReshapeFunc(Reshape);
    glutMainLoop ();
}
