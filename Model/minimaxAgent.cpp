#include "minimaxAgent.hpp"
#include <limits>
#include <iostream>

using namespace std;

double MinimaxAgent::Evaluate(const Game &game, int depth){
    if(depth <= 0){
	return game.Evaluate();
    }
    if(game.Turn() == MAXTURN){
	double max = -INFINITY;
	vector<Action> actions = game.GetLegalAction();
	for(int i = 0, size = actions.size(); i < size; i++){
	    Game tmp = game;
	    double value = Evaluate(tmp.ApplyAction(actions[i]), depth-1);

	    if(value > max)
		max = value;
	}
	return max;
    }
    else if(game.Turn() == MINTURN){
	double min = INFINITY;
	vector<Action> actions = game.GetLegalAction();
	for(int i = 0, size = actions.size(); i < size; i++){
	    Game tmp = game;
	    double value = Evaluate(tmp.ApplyAction(actions[i]), depth-1);
	    if(value < min)
		min = value;
	}
	return min;
    }
    else{
	cout <<"MinimaxAgent::Evaluate: Unrecognized turn" <<endl;
	return INFINITY;
    }
}

Action MinimaxAgent::GetAction(const Game&game, int depth){
    vector<Action> actions = game.GetLegalAction();
    int index = 0;
    if(game.Turn() == MAXTURN){
	double max = -INFINITY;
	for(int i = 0, size = actions.size(); i < size; i++){
	    Game tmp = game;
	    double value = Evaluate(tmp.ApplyAction(actions[i]), depth);
	    cout << actions[i] <<" " << value <<endl;
	    if( value>max){
		max = value;
		index = i;
	    }
	}

	cout << "PAcman : " ;
    }
    else if (game.Turn() == MINTURN){
	double min = INFINITY;
	for(int i = 0, size = actions.size(); i < size; i++){
	    Game tmp = game;
	    double value = Evaluate(tmp.ApplyAction(actions[i]), depth);
	    if( value<min){
		min = value;
		index = i;
	    }
	    cout << actions[i] <<" " << value <<endl;
	}
	cout << "Ghost ";
    }
    else{
	cout <<"MinimaxAgent::Evaluate: Unrecognized turn" <<endl;
    }

    cout << actions[index] <<endl;
    return actions[index];
}
