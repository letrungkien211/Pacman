#include "utility.hpp"
#include <vector>
#include <iostream>
#include <cstdio>
#include "gsearch.hpp"
#include "grid.hpp"

using namespace std;

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
    shortestPath.resize(size);
    for(int i = 0; i < size; i++){
	shortestPath[i].resize(size);
	for(int j =0; j<size; j++){
	    shortestPath[i][j] = "";
	}
    }
    //int cols = state->Cols();
    for(int i = 0; i <size-1; i++){
	for(int j = i+1; j < size; j++){
	    if(state->Wall(i) || state->Wall(j))
		continue;
	    shortestPath[i][j] = shortestPath[j][i] = PreCalculateMinDistance(state, i,j);
	}
    }
}

string Utility::PreCalculateMinDistance(State *state, int start, int goal){
    int cols = state->Cols();
    Gsearch<Grid, PQ<Grid, Grid::CompareByCost> > astar;
    astar.Type = ASTAR;
    Grid solution = astar(Grid(Position(start/cols, start%cols), "", state), 
			  Grid(Position(goal/cols, goal%cols), "", state));
    return solution.Path();
}

double Utility::Evaluate(const State & state){
    vector<double> features(NUMFEATURES);
    features[0] = PacmanToGhostDistance(state);
    features[1] = GhostToGhostDistance(state);
    features[2] = IsFinal(state);
    features[3] = NumFood(state);
    // features[3] = PacmanToNearestFood(state);

    // features[5] = NumGhostKilled(state);
    // features[6] = GhostDirection(state);
    double value = 0;
    // If terminal state
    if(features[2])
	return INFINITY*features[2];
    // If the two ghosts are next to each other 
    // and close to Pacman
    if(features[0] <6  && features[1]==1){
     	value += 100;
    }
    // If the two ghosts are far away from each other
    if(features[1]>=4)
	features[1] = 0;
    // If the two ghosts are overlap
    if(features[1] == 0)
	value += 100;
    value += coeff[0]*features[0] + coeff[1]*features[1]+coeff[2]*features[0]*features[1];
    return value;
}

double Utility::PacmanToGhostDistance(const State &state) const{
    double value = 0;
    int cols = state.Cols();
    int numGhost = state.NumGhost();
    int pacmanIndex = state.PacmanPosition().ToIndex(cols);

    for(int i = 0; i <numGhost; i++){
	int ghostIndex = state.GhostPosition(i).ToIndex(cols);
	string path = shortestPath[pacmanIndex][ghostIndex];
	double dis = shortestPath[pacmanIndex][ghostIndex].length();
	if(state.GhostScared(i))
	    value-=dis;
	else
	    value+=dis;

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
	    int distance= shortestPath[state.GhostPosition(i).ToIndex(cols)][state.GhostPosition(j).ToIndex(cols)].length();
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

double Utility::NumGhostKilled(const State &state) const{
    double value = 0;
    for(int i = 0; i < state.NumGhost(); i++){
	value += state.GhostKilled(i);
    }
    return value;
}
double Utility::GhostDirection(const State&state) const{
    double value = 0;
    int numGhost = state.NumGhost();
    for(int i = 0; i < numGhost-1; i++){
	for(int j = i+1; j<numGhost; j++){

	}
    }
    return value;
}
