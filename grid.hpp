#ifndef GRID_HPP
#define GRID_HPP

const Action ActionList[] ={UP, RIGHT, LEFT, DOWN, STOP};

class Grid{
private:
    Position pos;
    int cost;
    string path;
    State* state;
public:
    Grid(){
	cost = 0;
	path = "";
    }
    Grid(const Position& pos, const string &path, State* state){
	this->pos = pos;
	this->path = path;
	this->state = state;
    }

    bool operator==(const Grid &other){
	return other.Pos() ==Pos();
    }

    Grid(const Position &pos){
	this->pos = pos;
    }
    Position Pos() const{
	return pos;
    }
    Position &Pos(){
	return pos;
    }

    int Cost() const{
	return cost;
    }

    string Path() const{
	return path;
    }
    void MakeChildren(Stack<Grid> &childrenList) const{
	Grid child;
	for(int i = 0; i < 4; i++){
	    if(pos.IsLegal(ActionList[i], state->Rows(), state->Cols())){
		Position tmp = pos;
		tmp.Move(ActionList[i]);
		if(!state->Wall(tmp)){
		    string str(path);
		    str+=Action2Char(ActionList[i]);
		    childrenList.push(Grid(tmp, str, state));
		}
	    }
	}
    }

    void EvaluateCost(const Grid& goal){
	int man = Position::Manhattan(pos, goal.Pos());
	int len = path.length();
	cost = len+man;
    }
    
    class CompareByCost{
    public:
	bool operator()(const Grid &a, const Grid &b){
	    return a.Cost() > b.Cost();
	}
    };
    
    class CompareByState{
    public:
	bool operator()(const Grid &a, const Grid &b){
	    if(a.Pos().row<b.Pos().row)
		return true;
	    else if(a.Pos().row>b.Pos().row)
		return false;
	    else
		return a.Pos().col < b.Pos().col;
	}
    };
};

#endif
