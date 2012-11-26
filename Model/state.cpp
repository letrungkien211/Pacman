#include "state.hpp"

// int initFood[] ={1,1,1,1,1,
// 		 1,0,1,0,1,
// 		 1,1,0,1,1,
// 		 1,0,1,0,1,
// 		 1,1,1,1,1};
// int initWall[] ={0,0,0,0,0,
// 		 0,1,0,1,0,
// 		 0,0,0,0,0,
// 		 0,1,0,1,0,
// 		 0,0,0,0,0};

// int initFood[] ={1,1,1,1,1,1,1,1,
// 		 1,0,0,0,0,0,0,1,
// 		 1,1,1,1,1,1,1,1,
// 		 1,0,0,0,0,0,0,1,
// 		 1,0,0,0,0,0,0,1,
// 		 1,0,0,0,0,0,0,1,
// 		 1,1,1,1,1,1,1,1,
// 		 1,0,0,0,0,0,0,1,
// 		 1,1,1,1,1,1,1,1};
		 
// int initWall[] ={0,0,0,0,0,0,0,0,
// 		 0,1,0,1,1,1,1,0,
// 		 0,0,0,0,0,0,0,0,
// 		 0,1,1,0,0,1,1,0,
// 		 0,1,0,0,0,0,1,0,
// 		 0,1,1,1,1,1,1,0,
// 		 0,0,0,0,0,0,0,0,
// 		 0,1,1,1,1,1,1,0,
// 		 0,0,0,0,0,0,0,0};

const Action ActionList[] ={UP, DOWN, LEFT, RIGHT, STOP};

/*****************************************************************************/
// Constructor
State::State(){
}

// Static Initialization
void State::Initialize(int rows, int cols, bool[] wall){
    State::rows = rows;
    State::cols = cols;
    State::wall.resize(rows*cols);
    for(int i = 0, size = rows* cols; i < size; i++)
	State::wall = wall[i];
}

// Initialization
void State::Init(int[] food){
    // Food
    numFood = 0;
    for(int i = 0, size = rows* cols ; i <size; i++){
	this->food[i] = food[i];
	numFood += food[i];
    }
    
    // Ghost position
    ghostPos.resize(2);
    ghostPos[0].row = 0;
    ghostPos[0].col = 4;
    ghostPos[1].row = 0;
    ghostPos[1].col = 4;
    
    // Pacman postion
    pacmanPos.row = 8;
    pacmanPos.col = 5;

    // Turn
    turn = MAXTURN;
}

// Get next states
State State::GetNextState(Action pacmanAction){
    assert(!IsLegalPacmanAction(pacmanAction)); // Uncomment after finish projects
    
    pacmanPos.Move(action);

    switch(Food(pacmanPos)){
    case 2:
	MakeGhostScared(true);
    case 1:
	numFood--;
    default:
	MakeGhostScared(false);
	break;
    }

    return *this;
}

Result IsFinal() const{
    // Check collision with ghost
    for(int i =0, numGhost = ghostPos.size(); i < numGhost; i++){
	if(!ghostScared[i] && !Position::Manhattan(ghostPos[i], pacmanPos) ){
	    return LOSE;
	}
    }

    if(numFood == 0)
	return WIN;
    return UNKOWN;
}


bool State::IsLegalPamanAction(Action pacmanAction) const{
    if(pacmanPos.IsLegal(pacmanAction, rows, cols)){
	Position tmp = pacmanPos;
	tmp.Move(pacmanAction);
	if(!Wall(tmp))
	    return true;
    }
    return false;
}

bool State::IsLegalGhostAction(Action ghostAction, int ghostIndex) const{
    if(IsOppositeAction(ghostAction, previousGhostAction[ghostIndex]) 
       || ghostAction = STOP 
       || !ghostPos[ghostIndex].IsLegal(ghostAction, rows, cols)){
	return false;
    }

    Position tmp = ghostPos[ghostIndex];
    tmp.Move(ghostAction);
    if(Wall(tmp))
	return false;
    return true;
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
    return Food(pos.row, pos.col);
}
int &State::Food(Position pos){
    return Food(pos.row, pos.col);
}
bool State::Wall(int i, int j) const{
    assert(InRange(i,j,rows,cols));
    return wall[i*cols+j];
}
bool State::Wall(Position pos) const{
    return Wall(pos.row, pos.col);
}
int State::Turn() const{
    return turn;
}
int State::NumFood() const{
    return food;
}
int State::NumAction() const{
    return numAction;
}
bool State::GhostScared(int ghostIndex) const{
    return ghostScared[ghostIndex];
}
int State::Rows() const{
    return rows;
}
int State::Cols() const{
    return cols;
}
int State::Score() const{
    return score;
}

int State::NumGhost() const{
    return ghostPos.size();
}

/*****************************************************************************/

ostream & operator<<(ostream &os, const State& state){
    for(int i = 0, rows = state.Rows(); i <rows; i++){
	for(int j = 0, cols = state.Cols(); j<cols; j++){
	    if(state.Wall(i,j))
		os << "X";
	    else if (state.PacmanPosition().row == i && state.PacmanPosition().col == j){
		if (state.GhostPosition().row == i && state.GhostPosition().col ==j)
		    os << "D";
		else
		    os << "P";
	    }
	    else if (state.GhostPosition().row == i && state.GhostPosition().col ==j)
		os << "G";
	    else if(state(i,j).IsFood())
		os << "o";
	    else
		os << "-";
	}
	os << endl;
    }
    cout << "Number of food left: " << game.NumFood() <<endl;
    cout << "Turn: " << (game.Turn() ==MAXTURN ? "Pacman" : "Ghost" ) <<endl;
    return os;
}

