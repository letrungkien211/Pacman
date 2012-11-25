#include "minimaxAgent.hpp"
#include <limits>
#include <iostream>

using namespace std;

#define INFINITY numeric_limits<double>::max()

double MinimaxAgent::Evaluate(const Game &game, int depth){
    if(depth <= 0){
	return game.Evaluate();
    }
    if(game.Turn() == 0){
	double v = -INFINITY;
	vector<Action> actions = game.GetLegalAction();
	
    }
    else{

    }
}
