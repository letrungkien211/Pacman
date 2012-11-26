#include "state.hpp"
#include <cassert>

using namespace std;
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

State::State(int rows, int cols, bool wall[], int food[]){
    Initialize(rows, cols, wall, food);
}
// Static Initialization
void State::Initialize(int rows, int cols, bool wall[], int food[])
{
    this->rows = rows;
    this->cols = cols;
    this->wall.resize(rows*cols);
    this->food.resize(rows*cols);
    numFood = 0;
    score = 0;
    numAction = 0;
    previousGhostAction.resize(2);
    previousGhostAction[0] = STOP;
    previousGhostAction[1] = STOP;
    ghostScared.resize(2);
    ghostScared[0] = 0;
    ghostScared[1] = 0;
    
    // Init wall
    for(int i = 0, size = rows* cols; i < size; i++)
	this->wall[i] = wall[i];

    // Food
    for(int i = 0, size = rows* cols ; i <size; i++){
	this->food[i] = food[i];
	numFood += food[i];
    }
    // Ghost position
    ghostPos.resize(2);
    ghostPos[0].row = 0;
    ghostPos[0].col = 8;
    ghostPos[1].row = 0;
    ghostPos[1].col = 9;
    
    // Pacman postion
    pacmanPos.row = 8;
    pacmanPos.col = 8;
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
    case 2:
	MakeGhostScared(true);
    case 1:
	Food(pacmanPos) = false;
	numFood--;
    default:
	MakeGhostScared(false);
	break;
    }
//    turn = MINTURN;
    return *this;
}

// Get next state by moving ghosts
State State::GetNextState(const vector<Action>& ghostAction){
//    cout << "GetNextState" << ghostAction.size() << " " << ghostPos.size() <<endl;
    assert(ghostAction.size() == ghostPos.size());

    for(int i = 0, size = ghostAction.size(); i<size; i++){
	assert(IsLegalGhostAction(ghostAction[i], i));
	ghostPos[i].Move(ghostAction[i]);
    }
    previousGhostAction = ghostAction;
    return *this;
}

Result State::IsFinal() const{
    // Check collision with ghost
    for(int i =0, numGhost = ghostPos.size(); i < numGhost; i++){
	if(!ghostScared[i] && !Position::Manhattan(ghostPos[i], pacmanPos))
	    return LOSE;
    }


    if(numFood == 0)
	return WIN;
    return UNKOWN;
}

vector<Action > State::GetLegalPacmanAction() const{
    vector<Action> actions;
    for(int i = 0; i<5; i++){
	if(IsLegalPacmanAction(ActionList[i])){
	    actions.push_back(ActionList[i]);
	}
    }
    return actions;
}

vector<Action > State::GetLegalGhostAction(int ghostIndex) const{
    vector<Action> actions;
    for(int i = 0; i<5; i++){
	if(IsLegalGhostAction(ActionList[i], ghostIndex))
	    actions.push_back(ActionList[i]);
    }
    return actions;
} 
vector<vector<Action> > State::GetLegalCombinedGhostAction() const{
    return GetLegalCombinedGhostAction(NumGhost()-1);
}
vector<vector<Action> > State::GetLegalCombinedGhostAction(int ghostIndex) const{
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
bool State::IsLegalPacmanAction(Action pacmanAction) const{
    if(pacmanPos.IsLegal(pacmanAction, rows, cols)){
	Position tmp = pacmanPos;
	tmp.Move(pacmanAction);
	for(int i = 0; i<NumGhost(); i++)
	    if(!Position::Manhattan(tmp,ghostPos[i]))
		return false;
	if(!Wall(tmp))
	    return true;
    }
    return false;
}

bool State::IsLegalGhostAction(Action ghostAction, int ghostIndex) const{
    if(IsOppositeAction(ghostAction, previousGhostAction[ghostIndex]) 
       || ghostAction == STOP 
       || !ghostPos[ghostIndex].IsLegal(ghostAction, rows, cols)){
	return false;
    }

    Position tmp = ghostPos[ghostIndex];
    tmp.Move(ghostAction);
    if(Wall(tmp))
	return false;
    return true;
}
// Make ghost scared
void State::MakeGhostScared(bool scared){
    if(scared){
	for(int i = 0; i < NumGhost(); i++){
	    ghostScared[i] = numAction;
	}
    }
    else{
	for(int i = 0; i< NumGhost(); i++){
	    if(numAction-ghostScared[i]>SCARETIMOUT)
		ghostScared[i] = 0;
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
    return Food(pos.row, pos.col);
}
int &State::Food(Position pos){
    return Food(pos.row, pos.col);
}
bool State::Wall(int i) const{
    assert(i<rows*cols && i>=0);
    return wall[i];
}
bool State::Wall(int i, int j) const{
    assert(InRange(i,j,rows,cols));
    return wall[i*cols+j];
}
bool State::Wall(Position pos) const{
    return Wall(pos.row, pos.col);
}
// int State::Turn() const{
//     return turn;
// }
int State::NumFood() const{
    return numFood;
}
int State::NumAction() const{
    return numAction;
}
int State::GhostScared(int ghostIndex) const{
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

Position State::PacmanPosition() const{
    return pacmanPos;
}

Position State::GhostPosition(int ghostIndex) const{
    return ghostPos[ghostIndex];
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
    //cout << "Turn: " << (state.Turn() ==MAXTURN ? "Pacman" : "Ghost" ) <<endl;
    return os;
}

