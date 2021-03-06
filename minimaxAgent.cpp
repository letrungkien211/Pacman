#include "minimaxAgent.hpp"
#include <limits>
#include <iostream>
#include <cassert>
#include <ctime>
#include <cstdlib>
using namespace std;

double MinimaxAgent::Evaluate(const State &state, int depth, int player){
    numIteration++;
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
    double max = -INFINITY;

    int index = 0;
    for(int i = 0, size = pacmanActions.size(); i < size; i++){
	State tmp = state;
	double value = Evaluate(tmp.GetNextState(pacmanActions[i]), depth, MINTURN);
	if( value>max){
	    max = value;
	    index = i;
	}
    }
    if(v) 
	*v = max;
    return pacmanActions[index];
}


vector<Action>  MinimaxAgent::ChooseCombinedGhostAction(const State&state, int depth, double level, double *v){
    if(!state.NumGhost())
	return vector<Action>(0);
    vector<vector<Action> > combinedGhostActions = state.GetLegalCombinedGhostAction();
    double min = INFINITY;
    int index = 0;
    numIteration = 0;
    int size = combinedGhostActions.size();
    for(int i = 0; i < size; i++){
	State tmp = state;
	double value = Evaluate(tmp.GetNextState(combinedGhostActions[i]), depth, MAXTURN);
	if( value<min){
	    min = value;
	    index = i;
	}
    }
    cout <<"Number of Evaluate: "<< numIteration <<endl;
    cout << "Minvalue: " << min << endl;
    if(v) 
	*v = min;
    
    if(rand()/(double)RAND_MAX<level)
	return combinedGhostActions[index];
    else
	return combinedGhostActions[rand()%size];
}

