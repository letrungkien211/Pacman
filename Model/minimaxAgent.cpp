#include "minimaxAgent.hpp"
#include <limits>
#include <iostream>
#include <cassert>

using namespace std;

double MinimaxAgent::Evaluate(const State &state, int depth, int player){
    if(depth <= 0 || state.IsFinal()!=UNKOWN){
	return Utility::Evaluate(state);
    }

    if(player == MAXTURN){
	double v = -INFINITY;
	vector<Action> actions = state.GetLegalPacmanAction();
	for(int i = 0, size = actions.size(); i < size; i++){
	    State tmp = state;
	    v = max(v, Evaluate(tmp.GetNextState(actions[i]), depth-1, MINTURN));
	}
	return v;
    }
    else{
	double v = INFINITY;
	vector<vector<Action> > combinedGhostActions = state.GetLegalCombinedGhostAction();
	for(int i = 0, size = combinedGhostActions.size(); i < size; i++){
	    State tmp = state;
	    v=min(v, Evaluate(tmp.GetNextState(combinedGhostActions[i]), depth-1, MAXTURN));
	}
	return v;
    }
}

Action MinimaxAgent::ChoosePacmanAction(const State&state, int depth, double *v){
    vector<Action> pacmanActions = state.GetLegalPacmanAction();

    //  assert(state.Turn() == MAXTURN);
    double max = -INFINITY;
    int index = 0;
    for(int i = 0, size = pacmanActions.size(); i < size; i++){
	State tmp = state;
	double value = Evaluate(tmp.GetNextState(pacmanActions[i]), depth, MINTURN);
	//cout << pacmanActions[i] <<" " << value <<endl;
	if( value>max){
	    max = value;
	    index = i;
	}
    }
    *v = max;
    return pacmanActions[index];
}


vector<Action>  MinimaxAgent::ChooseCombinedGhostAction(const State&state, int depth, double *v){
    vector<vector<Action> > combinedGhostActions = state.GetLegalCombinedGhostAction();
    //   assert (state.Turn() == MINTURN);
    double min = INFINITY;
    int index = 0;
    for(int i = 0, size = combinedGhostActions.size(); i < size; i++){
	State tmp = state;
	double value = Evaluate(tmp.GetNextState(combinedGhostActions[i]), depth, MAXTURN);
//	cout << combinedGhostActions[i]<< " "<< value <<endl;
	if( value<min){
	    min = value;
	    index = i;
	}
    }
    *v = min;
    return combinedGhostActions[index];
}
