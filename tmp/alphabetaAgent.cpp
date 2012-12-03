#include "alphabetaAgent.hpp"

double AlphaBetaAgent::Evaluate(const State &state, int depth, int player){
    return Evaluate(state, depth, player, -INFINITY, +INFINITY);
}
double AlphaBetaAgent::Evaluate(const State &state, int depth, int player, double alpha, double beta){
    if(depth <= 0 || state.IsFinal()!=UNKOWN){
	return Utility::Evaluate(state);
    }
    numIteration++;
    if(player == MAXTURN){
	double v = -INFINITY;
	vector<Action> actions = state.GetLegalPacmanAction();
	for(int i = 0, size = actions.size(); i < size; i++){
	    State tmp = state;
	    v = max(v, Evaluate(tmp.GetNextState(actions[i]), depth-1, MINTURN, alpha, beta));
	    alpha = max(alpha, v);
	    if(alpha >= beta)
		return alpha;
	}
	return v;
    }
    else{
	double v = INFINITY;
	vector<vector<Action> > combinedGhostActions = state.GetLegalCombinedGhostAction();
	for(int i = 0, size = combinedGhostActions.size(); i < size; i++){
	    State tmp = state;
	    v=min(v, Evaluate(tmp.GetNextState(combinedGhostActions[i]), depth-1, MAXTURN, alpha, beta));
	    beta = min(beta, v);
	    if(alpha>=beta)
		return beta;
	}
	return v;
    }
}

