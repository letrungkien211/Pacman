#include "game.hpp"

int initFood[] ={1,1,1,1,1,
		 1,0,1,0,1,
		 1,1,0,1,1,
		 1,0,1,0,1,
		 1,1,1,1,1};
int initWall[] ={0,0,0,0,0,
		 0,1,0,1,0,
		 0,0,0,0,0,
		 0,1,0,1,0,
		 0,0,0,0,0};

const Action ActionList[] ={STOP, UP, DOWN, LEFT, RIGHT};

/*****************************************************************************/
Game::Game(int rows, int cols){
    this->rows = rows;
    this->cols = cols;
    m.resize(rows*cols);
}

void Game::Init(){
    for(int i = 0, size = rows* cols ; i <size; i++){
	(*this)(i).SetFood(initFood[i]);
	(*this)(i).SetWall(initWall[i]);
    }
    ghostPos.row = 4;
    ghostPos.col = 0;
    pacmanPos.row = 2;
    pacmanPos.col = 2;
    numFood = 20;
    turn = MAXTURN;
}

Result Game::Res() const{
    return res;
}

Game Game::ApplyAction(Action action){
    if(!IsLegalAction(action)){
	cout << action <<" is not a legal action!" <<endl;
	return *this;
    }
    
    if(turn == MAXTURN){
	pacmanPos.Move(action);
	turn = MINTURN;
    }
    else if(turn == MINTURN){
	ghostPos.Move(action);
	turn = MAXTURN;
    }
    if((*this)(pacmanPos.row, pacmanPos.col).IsFood()){
	(*this)(pacmanPos.row, pacmanPos.col).SetFood(false);
	numFood--;
    }

    res = UNKOWN;
    if(ghostPos.row == pacmanPos.row && ghostPos.col == pacmanPos.col)
	res = LOSE;
    else if(numFood == 0)
	res = WIN;

    return *this;
}

bool Game::IsLegalAction(Action action) const{
    if(turn == MAXTURN){
	if(pacmanPos.IsLegal(action, rows, cols)){
	    Position tmp = pacmanPos;
	    tmp.Move(action);
	    if(!(*this)(tmp.row, tmp.col).IsWall())
		return true;
	}
    }

    else if(turn == MINTURN){
	if(ghostPos.IsLegal(action, rows, cols)){
	    Position tmp = ghostPos;
	    tmp.Move(action);
	    if(!(*this)(tmp.row, tmp.col).IsWall())
		return true;
	}
    }

    return false;
}

vector<Action> Game::GetLegalAction() const{
    vector<Action> actions;
    for(int i = 0; i < 5; i++){
	if(IsLegalAction(ActionList[i]))
	    actions.push_back(ActionList[i]);
    }
    return actions;
}

double Game::Evaluate() const{
    return Position::Manhattan(pacmanPos, ghostPos);
}


/*****************************************************************************/
/*Element access*/
Cell Game::operator()(int i, int j) const{
    return m[i*cols+j];
}

Cell& Game::operator()(int i, int j){
    return m[i*cols+j];
}

Cell Game::operator()(int i) const{
    return m[i];
}

Cell& Game::operator()(int i){
    return m[i];
}

int Game::Turn() const{
    return turn;
}

int Game::NumFood() const{
    return numFood;
}

int Game::Rows() const{
    return rows;
}

int Game::Cols() const{
    return cols;
}

Position Game::PacmanPosition() const{
    return pacmanPos;
}

Position Game::GhostPosition() const{
    return ghostPos;
}

/*****************************************************************************/

ostream & operator<<(ostream &os, const Game& game){
    for(int i = 0, rows = game.Rows(); i <rows; i++){
	for(int j = 0, cols = game.Cols(); j<cols; j++){
	    if(game(i,j).IsWall())
		os << "X";
	    else if (game.PacmanPosition().row == i && game.PacmanPosition().col == j){
		if (game.GhostPosition().row == i && game.GhostPosition().col ==j)
		    os << "D";
		else
		    os << "P";
	    }
	    else if (game.GhostPosition().row == i && game.GhostPosition().col ==j)
		os << "G";
	    else if(game(i,j).IsFood())
		os << "o";
	    else
		os << "-";
	}
	os << endl;
    }
    cout << "Number of food left: " << game.NumFood() <<endl;
    cout << "Turn: " << (game.Turn() ==0 ? "Pacman" : "Ghost" ) <<endl;
    return os;
}

