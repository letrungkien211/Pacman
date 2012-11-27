#include "utility.hpp"

#include <vector>
#include <iostream>
#include <cstdio>
#include "gsearch.hpp"
#include "grid.hpp"
using namespace std;

int NUMFEATURES = 5;

Utility::Utility(){
    coeff.resize(NUMFEATURES);
}

Utility::Utility(const vector<double> &coeff){
    this->coeff = coeff;
}

void Utility::SetCoeff(const vector<double> &coeff){
    this->coeff = coeff;
}

void Utility::PreCalculateMinDistance(State *state){
    int size = state->Rows()*state->Cols();
    vector<bool> marked;
    minDistance.resize(size);
    for(int i = 0; i < size; i++){
	minDistance[i].resize(size);
	for(int j =0; j<size; j++){
	    minDistance[i][j] = 0;
	}
    }
    int cols = state->Cols();
    for(int i = 0; i <size-1; i++){
	for(int j = i+1; j < size; j++){
	    if(state->Wall(i) || state->Wall(j))
		continue;
	    minDistance[i][j] = minDistance[j][i] = PreCalculateMinDistance(state, i,j);
	    printf("(%d,%d) -> (%d, %d) : %d\n", i/cols, i%cols, j/cols, j%cols
		   ,minDistance[i][j]);
	}
    }
}

int Utility::PreCalculateMinDistance(State *state, int start, int goal){
    int cols = state->Cols();
    Gsearch<Grid, PQ<Grid, Grid::CompareByCost> > astar;
    astar.Type = ASTAR;
    Grid solution = astar(Grid(Position(start/cols, start%cols), "", state), 
			  Grid(Position(goal/cols, goal%cols), "", state));
    cout << solution.Path()<<endl;
    return solution.Path().length();
}


double Utility::Evaluate(const State & state){
    vector<double> features(NUMFEATURES);
    features[0] = PacmanToGhostDistance(state);
    features[1] = PacmanToNearestFood(state);
    features[2] = NumFood(state);
    features[3] = GhostToGhostDistance(state);
    features[4] = IsFinal(state);
    double value = 0;
    for(int i = 0, size = features.size(); i<size; i++){
	value +=features[i]*coeff[i];
    }
    return value;
}

double Utility::PacmanToGhostDistance(const State &state) const{
    double value = 0;
    int pacmanIndex = state.PacmanPosition().row*state.Cols() + state.PacmanPosition().col;
    for(int i = 0; i <state.NumGhost(); i++){
	int ghostIndex = state.GhostPosition(i).row*state.Cols() + state.GhostPosition(i).col;
	double dis = minDistance[pacmanIndex][ghostIndex];
	value+= state.GhostScared(i) ? -dis: dis;
    }
    return value;
}

double Utility::NumFood(const State &state) const{
    return state.NumFood();
}

double Utility::PacmanToNearestFood(const State &state) const{
    return 0;
}

double Utility::GhostToGhostDistance(const State &state) const{
    double value = 0;
    int num = state.NumGhost();
    int cols = state.Cols();
    for(int i = 0; i< num-1; i++){
	for(int j = i+1; j< num; j++){
	    int distance= minDistance[state.GhostPosition(i).ToIndex(cols)][state.GhostPosition(j).ToIndex(cols)];
	    value+=distance;
	} 
    }
    return value;
}

double Utility::IsFinal(const State &state) const{
    switch(state.IsFinal()){
    case WIN:
	return 1;
    case LOSE:
	return -1;
    default:
	return 0;
    }
}
