#include "common.hpp"
#include <iostream>
#include <cmath>

using namespace std;

void Position::Move(Action action){
    switch(action){
    case UP:   row--; break;
    case DOWN: row++; break;
    case LEFT: col--; break;
    case RIGHT:col++; break;
    case STOP:
	break;
    default:
	cout << "Unrecognized action" <<endl;
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

double Position::Manhattan(const Position& p, const Position & q){
    return abs(p.row-q.row) + abs(p.col-q.col);
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
    case LOSE: os << "LOSE";
    case WIN: os << "WIN" ;
    case UNKOWN: os <<"UNKOWN";
    default:
	cout <<"operator<<(result): Unrecognized result"<<endl;
	break;
    }
    return os;
}
