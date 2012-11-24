#include "board.hpp"

Board::Board(int rows, int cols){
    this->rows = rows;
    this->cols = cols;
    m.resize(rows*cols);
}


int initFood[] ={1,1,1,1,1,
		 1,0,1,0,1,
		 1,1,0,1,1,
		 1,1,1,1,1,
		 1,0,1,0,1};
int initWall[] ={0,0,0,0,0,
		 0,1,0,1,0,
		 0,0,0,0,0,
		 0,1,0,1,0,
		 0,0,0,0,0};
		 

void Board::Init(){
    for(int i = 0, size = rows* cols ; i <rows; i++){
	(*this)(i).SetFood(initFood[i]);
	(*this)(i).SetWall(initWall[i]);
    }
}

Cell Board::operator(int i, int j) const{
    return m[i*cols+j];
}

Cell& Board::operator(int i, int j){
    return m[i*cols+j];
}

Cell Board::operator(int i) const{
    return m[i];
}

Cell& Board::operator(int i){
    return m[i];
}

int Board::Rows() const{
    return rows;
}
int Board::Cols() const{
    return cols;
}


ostream & operator<<(ostream &os, const Board& board){
    for(int i = 0, rows = board.Rows(); i <rows; i++){
	for(int j = 0, cols = board.Cols(); j<cols; j++){
	    if(
	}
    }
}
