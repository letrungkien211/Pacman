#include "common.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <cassert>
#include <cctype>

using namespace std;

bool IsOppositeAction(Action a, Action b){
    return (a == LEFT && b == RIGHT) 
	||(b == LEFT && a == RIGHT) 
	|| (a== UP && b == DOWN)
	|| (b== UP && a == DOWN);
}

bool InRange(int i, int j, int rows, int cols){
    return InRange(i,0,rows-1) && InRange(j,0,cols-1);
}

bool InRange(int i, int min, int max){
    return i>= min && i<=max;
}

Action Char2Action(char c){
    switch(tolower(c)){
    case 's':
	return STOP;
    case 'u':
	return UP;
    case 'l':
	return LEFT;
    case 'r':
	return RIGHT;
    case 'd':
	return DOWN;
    default:
	break;
    }

    return STOP;
}

char Action2Char(Action action){
    switch(action){
    case UP:   return 'u';
    case DOWN: return 'd';
    case LEFT: return 'l';
    case RIGHT: return 'r';
    case STOP: return 's';
    default:
	cout << "Unrecognized action" <<endl;
	break;
    }
    return 's';
}

void Position::Move(Action action){
    switch(action){
    case UP:   
	row--; 
	break;
    case DOWN: 
	row++; 
	break;
    case LEFT: 
	col--; 
	break;
    case RIGHT:
	col++; 
	break;
    case STOP:
	break;
    default:
	break;
    }
}

bool Position::IsLegal(Action action, int rows, int cols) const{
    bool legal = true;
    switch(action){
    case UP:   
	if(row<=0)
	    legal = false;
	break;
    case DOWN: 
	if(row>=rows-1)
	    legal = false;
	break;
    case LEFT: 
	if(col<=0)
	    legal = false;
	break;
    case RIGHT:
	if(col>=cols-1)
	    legal = false;
	break;
    case STOP:
	break;
    default:
	cout << "Position::IsLegal: Unrecognized action" <<endl;
	break;
    }
    
    return legal;
}

Position::Position(){
    row = col = 0;
}
Position::Position(int row, int col){
    this->row = row; 
    this->col = col;
}
bool Position::Equal(Position pos) const{
  return row==pos.row && col==pos.col;
}

bool Position::Equal(int i, int j) const{
  return row == i && col == j;
}
double Position::Manhattan(const Position& p, const Position & q){
    return std::abs(p.row-q.row) + std::abs(p.col-q.col);
}


int Position::ToIndex(int cols) const{
    return row*cols+ col;
}
bool Position::operator==(Position &other) const{
    return row == other.row && col == other.col; 
}

ostream &operator<<(ostream &os, Action action){
    switch(action){
    case UP:   os<<"U"; break;
    case DOWN: os<<"D"; break;
    case LEFT: os<<"L"; break;
    case RIGHT:os<<"R"; break;
    case STOP:os<<"S"; break;
    default:
	cout << "operator<<(action): Unrecognized action" <<endl;
	break;
    }
    return os;
}
ostream &operator<<(ostream &os, Result result){
    switch(result){
    case LOSE: os << "LOSE"; break;
    case WIN: os << "WIN" ; break;
    case UNKOWN: os <<"UNKOWN"; break;
    default:
	cout <<"operator<<(result): Unrecognized result"<<endl;
	break;
    }
    return os;
}

ostream &operator<<(ostream &os, vector<Action> &action){
    os <<"(";
    for(int i=0, size = action.size(); i<size; i++)
	cout <<action[i] <<", ";
    os <<")";
    return os;
}

ostream &operator<<(ostream &os, Position pos){
    os<<" ("<<pos.row<<","<<pos.col<<") ";
    return os;
}
