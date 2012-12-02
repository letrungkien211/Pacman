#include "state.hpp"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <GL/glut.h>
using namespace std;
const Action ActionList[] ={UP, DOWN, LEFT, RIGHT, STOP};

/*****************************************************************************/
// Constructor
State::State(){
    wall = NULL;
    numFood = 0;
}

State::State(int rows, int cols, bool *wall, int *food){
    Initialize(rows, cols, wall, food);
}

// Static Initialization
void State::Initialize(int rows, int cols, bool *wall, int *food)
{
    this->rows = rows;
    this->cols = cols;
    this->food.resize(rows*cols);
    numFood = 0;
    previousGhostAction.resize(2);
    previousGhostAction[0] = STOP;
    previousGhostAction[1] = STOP;
    ghostScared.resize(2);
    ghostScared[0] = false;
    ghostScared[1] = false;
    
    // Init wall
    // this->wall = new bool[rows*cols];
    // for(int i = 0, size = rows* cols; i < size; i++)
    // 	this->wall[i] = wall[i];

    this->wall = wall;

    // Food
    for(int i = 0, size = rows* cols ; i <size; i++){
	this->food[i] = food[i];
	numFood += food[i];
	if(wall[i] && food[i])
	    cout << "Wrong input: " << i <<endl;
	assert(!wall[i] || !food[i]);
	
    }
    // Ghost position
    ghostPos.resize(2);
    ghostPos[0].row = 1;
    ghostPos[0].col = 9;
    ghostPos[1].row = 1;
    ghostPos[1].col = 10;
    
    // Pacman postion
    pacmanPos.row = 9;
    pacmanPos.col = 9;
}

// Finalize the state
void State::Finalize(){
    //delete wall;
}

// Get next state
State State::GetNextState(Action pacmanAction, const vector<Action> &ghostAction){
    GetNextState(pacmanAction);
    GetNextState(ghostAction);

    return *this;
}

// Get next state by moving pacman
State State::GetNextState(Action pacmanAction){
    assert(IsLegalPacmanAction(pacmanAction)); // Uncomment after finish projects
    pacmanPos.Move(pacmanAction);

    switch(Food(pacmanPos)){
    case 10:
	MakeGhostScared(true);
    case 1:
	numFood -= Food(pacmanPos);
	Food(pacmanPos) = 0;
	break;
    default:
	MakeGhostScared(false);
	break;
    }
    for(int i = NumGhost()-1 ; i >=0; i--){
	if(GhostKilled(i)){
	    ghostPos.erase(ghostPos.begin()+i);
	    ghostScared.erase(ghostScared.begin()+i);
	    previousGhostAction.erase(previousGhostAction.begin()+i);
	    cout << "Kill a ghost!" <<endl;
	}
    }

    return *this;
}

// Get next state by moving ghosts
State State::GetNextState(const vector<Action>& ghostAction){
    assert(ghostAction.size() == ghostPos.size());

    for(int i = 0, size = ghostAction.size(); i<size; i++){
	if(!IsLegalGhostAction(ghostAction[i], i)){
	    cout << "Attempted Ilegal Move" << i << " " <<ghostAction[i] <<endl;
	}
	// assert(IsLegalGhostAction(ghostAction[i], i));
	ghostPos[i].Move(ghostAction[i]);
    }
    previousGhostAction = ghostAction;



    return *this;
}

// Check if the game ends or not
Result State::IsFinal() const{
    // Check collision with ghost
    for(int i =0, numGhost = ghostPos.size(); i < numGhost; i++){
	if(!ghostScared[i] && !Position::Manhattan(ghostPos[i], pacmanPos))
	    return LOSE;
    }

    if(!numFood || !NumGhost())
	return WIN;
    return UNKOWN;
}

// Get legal pacman actions
vector<Action > State::GetLegalPacmanAction() const{
    vector<Action> actions;
    for(int i = 0; i<5; i++){
	if(IsLegalPacmanAction(ActionList[i])){
	    actions.push_back(ActionList[i]);
	}
    }
    return actions;
}

// Get legal ghost[i] actions
vector<Action > State::GetLegalGhostAction(int ghostIndex) const{
    vector<Action> actions;
    for(int i = 0; i<4; i++){
	if(IsLegalGhostAction(ActionList[i], ghostIndex))
	    actions.push_back(ActionList[i]);
    }
    if(actions.empty())
	actions.push_back(STOP);
    return actions;
} 

// Get legal combined ghosts actions
vector<vector<Action> > State::GetLegalCombinedGhostAction() const{
    return GetLegalCombinedGhostAction(NumGhost()-1);
}

// Get legal combined ghosts actions recursive version
vector<vector<Action> > State::GetLegalCombinedGhostAction(int ghostIndex) const{
    if(!NumGhost())
	return vector<vector<Action> >(0);
    vector<vector<Action> > combinedGhostAction;
    if(ghostIndex <=0){
	vector<Action> legalGhostAction = GetLegalGhostAction(ghostIndex);
	int size = legalGhostAction.size();
	combinedGhostAction.resize(size);
	for(int i =0; i< size; i++){
	    combinedGhostAction[i].push_back(legalGhostAction[i]);
	}
    }
    else{
	vector<vector<Action> > previousCombinedGhostAction = GetLegalCombinedGhostAction(ghostIndex-1);
	vector<Action> legalGhostAction = GetLegalGhostAction(ghostIndex);

	while(!previousCombinedGhostAction.empty()){
	    for(unsigned int i = 0; i<legalGhostAction.size(); i++){
		vector<Action> combined = previousCombinedGhostAction.back();
		combined.push_back(legalGhostAction[i]);
		combinedGhostAction.push_back(combined);
	    }
	    previousCombinedGhostAction.pop_back();
	}
    }
    return combinedGhostAction;
}

// Check if an action is legal for pacman
bool State::IsLegalPacmanAction(Action pacmanAction) const{
    if(pacmanPos.IsLegal(pacmanAction, rows, cols)){
	Position tmp = pacmanPos;
	tmp.Move(pacmanAction);
	for(int i = 0; i<NumGhost(); i++)
	    if(!ghostScared[i] && !Position::Manhattan(tmp,ghostPos[i]))
		return false;
	if(!Wall(tmp))
	    return true;
    }
    return false;
}

// Check if an acti<ons is legal for ghost[i]
bool State::IsLegalGhostAction(Action ghostAction, int ghostIndex) const{
    if(IsOppositeAction(ghostAction, previousGhostAction[ghostIndex]) 
       || !ghostPos[ghostIndex].IsLegal(ghostAction, rows, cols)){
	return false;
    }

    Position tmp = ghostPos[ghostIndex];
    tmp.Move(ghostAction);
    if(Wall(tmp) || (ghostScared[ghostIndex] && !Position::Manhattan(tmp, pacmanPos)))
	return false;

    return true;
}

// Make ghost scared or not by using a local timer
void State::MakeGhostScared(bool scared){
    static int timer = 0;
    if(scared){
	for(int i = 0; i < NumGhost(); i++){
	    ghostScared[i] = true;
	}
	timer = 0;
    }
    else{
	if(timer>SCARETIMOUT){
	    for(int i = 0; i< NumGhost(); i++){
		ghostScared[i] = false;
	    }
	    timer = 0;
	}
	else {
	    timer++;
	}
    }
}

/*****************************************************************************/

/*Element Access*/
int State::Food(int i, int j) const{
    assert(InRange(i,j,rows,cols));
    return food[i*cols+j];
}

int &State::Food(int i, int j){
    assert(InRange(i,j,rows,cols));
    return food[i*cols+j];
}
int State::Food(Position pos) const{
    assert(InRange(pos.row, pos.col, rows, cols));
    return Food(pos.row, pos.col);
}
int &State::Food(Position pos){
    assert(InRange(pos.row, pos.col, rows, cols));
    return Food(pos.row, pos.col);
}
bool State::Wall(int i) const{
    assert(i<rows*cols && i>=0);
    assert(wall);
    return wall[i];
}
bool State::Wall(int i, int j) const{
    assert(InRange(i,j,rows,cols));
    assert(wall);
    return wall[i*cols+j];
}
bool State::Wall(Position pos) const{
    assert(InRange(pos.row, pos.col, rows, cols));
    assert(wall);
    return Wall(pos.row, pos.col);
}
int State::NumFood() const{
    return numFood;
}

int State::GhostScared(int ghostIndex) const{
    assert(ghostIndex<NumGhost());
    return ghostScared[ghostIndex];
}

bool State::GhostKilled(int ghostIndex) const{
    return ghostScared[ghostIndex] && !Position::Manhattan(pacmanPos, ghostPos[ghostIndex]);
}

int State::Rows() const{
    return rows;
}
int State::Cols() const{
    return cols;
}

int State::NumGhost() const{
    return ghostPos.size();
}

Position State::PacmanPosition() const{
    return pacmanPos;
}

Position State::GhostPosition(int ghostIndex) const{
    assert(ghostIndex<NumGhost());
    return ghostPos[ghostIndex];
}

Action State::PreviousGhostAction(int ghostIndex) const{
    return previousGhostAction[ghostIndex];
}

/*****************************************************************************/

ostream & operator<<(ostream &os, const State& state){
    for(int i = 0, rows = state.Rows(); i <rows; i++){
	for(int j = 0, cols = state.Cols(); j<cols; j++){
	    if(state.Wall(i,j))
		os<<"X";
	    else if(state.PacmanPosition().Equal(i,j)){
		int k;
		for(k = 0; k < state.NumGhost(); k++){
		    if(state.PacmanPosition().Equal(state.GhostPosition(k))){
			os <<"D";
			break;
		    }
		}
		if(k==state.NumGhost())
		    os<<"P";
	    }
	    else {
		int k;
		for(k = 0; k < state.NumGhost(); k++){
		    if(state.GhostPosition(k).Equal(i,j)){
			if(state.GhostScared(k))
			    os <<"S";
			else
			    os<< "G";
			break;
		    }
		}
		if(k==state.NumGhost()){
		    if(state.Food(i,j)==1)
			cout << "-";
		    else if(state.Food(i,j)==10)
			cout << "o";
		    else
			cout << " ";
		}
	    }
	}
	cout <<endl;
    }
    cout << "Number of food left: " << state.NumFood() <<endl;
    cout << endl;
    return os;
}

void glRectf(double left,double right, double top, double down){
    glBegin(GL_QUADS);
    glVertex2d(left, top);
    glVertex2d(left, down);
    glVertex2d(right, down);
    glVertex2d(right, top);
    glEnd();
}


void DrawWall(int i, int j){
    i = i- 4;
    j = j- 9;
    glColor3d(0,1,0);
    glRectf(j-0.5,j+0.5,i-0.5,i+0.5);
    // glPointSize(20);
    // glBegin(GL_POINTS);
    // glVertex2d(j,i);
    // glEnd();
}

void DrawFood(int i, int j){
    i = i- 4;
    j = j- 9;
    glColor3d(1,0,0);
    glPointSize(5);
    glBegin(GL_POINTS);
    glVertex2d(j,i);
    glEnd();

}

void DrawGhost(int i,int j){
    i = i- 4;
    j = j- 9;
    glColor3d(1,0,1);
    glRasterPos3d(j-0.25, i+0.25, 0);
    glutBitmapCharacter (GLUT_BITMAP_HELVETICA_18, 'G');

}

void DrawScraredGhost(int i,int j){
    i = i- 4;
    j = j- 9;

    glColor3d(0.3,0,0.5);
    glRasterPos2d(j-0.25, i-0.25);
    glutBitmapCharacter (GLUT_BITMAP_HELVETICA_18, 'S');

}

void DrawPacman(int i, int j){
    i = i- 4;
    j = j- 9;
    glColor3d(0,0,1);
    glRectf(j-0.2, j+0.2, i-0.2,i+0.2);
}

void DrawBigFood(int i, int j){
    i = i- 4;
    j = j- 9;
    glColor3d(0,0,1);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2d(j,i);
    glEnd();

}

void GameDraw(const State& state){
    if(state.IsFinal()==UNKOWN){
	cout << state <<endl;
    }
    else{
	cout << "Pacman: " << state.IsFinal() <<endl;
    }

    for(int i = 0, rows = state.Rows(); i <rows; i++){
	for(int j = 0, cols = state.Cols(); j<cols; j++){
	    if(state.Wall(i,j))
		DrawWall(i,j);
	    else {
		if(state.PacmanPosition().Equal(i,j)){
		    DrawPacman(i,j);
		}
		int k;
		for(k = 0; k < state.NumGhost(); k++){
		    if(state.GhostPosition(k).Equal(i,j)){
			if(state.GhostScared(k))
			    DrawScraredGhost(i,j);
			else
			    DrawGhost(i,j);
			break;
		    }
		}
		if(state.Food(i,j)==1)
		    DrawFood(i,j);
		else if(state.Food(i,j)==10)
		    DrawBigFood(i,j);
	    }
	}
    }
}

