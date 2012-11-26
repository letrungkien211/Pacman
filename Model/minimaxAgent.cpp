#include "minimaxAgent.hpp"
#include <limits>
#include <iostream>
#include <cassert>

using namespace std;

double MinimaxAgent::Evaluate(const State &state, int depth){
    if(depth <= 0){
	return Utility::Evaluate(state);
    }
    if(state.Turn() == MAXTURN){
	double max = -INFINITY;
	vector<Action> actions = state.GetLegalPacmanAction();
	for(int i = 0, size = actions.size(); i < size; i++){
	    State tmp = state;
	    double value = Evaluate(tmp.GetNextState(actions[i]), depth-1);
	    if(value > max)
		max = value;
	}
	return max;
    }
    else{
	double min = INFINITY;
	vector<vector<Action> > combinedActions = state.GetLegalCombinedGhostAction();
	for(int i = 0, size = combinedActions.size(); i < size; i++){
	    State tmp = state;
	    double value = Evaluate(tmp.GetNextState(combinedActions[i]), depth-1);
	    if(value < min)
		min = value;
	}
	return min;
    }
}


Action MinimaxAgent::ChoosePacmanAction(const State&state, int depth){
    vector<Action> pacmanActions = state.GetLegalPacmanAction();
    int index = 0;
    assert(state.Turn() == MAXTURN);
    
    double max = -INFINITY;
    for(int i = 0, size = pacmanActions.size(); i < size; i++){
	State tmp = state;
	double value = Evaluate(tmp.GetNextState(pacmanActions[i]), depth);
	//cout << pacmanActions[i] <<" " << value <<endl;
	if( value>max){
	    max = value;
	    index = i;
	}
    }
    return pacmanActions[index];
}


vector<Action>  MinimaxAgent::ChooseCombinedGhostAction(const State&state, int depth){
    vector<vector<Action> > combinedGhostActions = state.GetLegalCombinedGhostAction();
    assert (state.Turn() == MINTURN);
    double min = INFINITY;
    int index = 0;
    for(int i = 0, size = combinedGhostActions.size(); i < size; i++){
	State tmp = state;
	double value = Evaluate(tmp.GetNextState(combinedGhostActions[i]), depth);
	if( value<min){
	    min = value;
	    index = i;
	}
    }
    return combinedGhostActions[index];
}

