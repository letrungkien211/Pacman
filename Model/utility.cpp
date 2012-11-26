#include "utility.hpp"

#include <vector>
#include <iostream>

using namespace std;

Utility::Utility(){
    coeff.resize(3);
}

Utility::Utility(const vector<double> &coeff){
    this->coeff = coeff;
}

void Utility::SetCoeff(const vector<double> &coeff){
    this->coeff = coeff;
}

double Utility::Evaluate(const State & state){
    vector<double> features(3);
    features[0] = PacmanToGhostDistance(state);
    features[1] = PacmanToNearestFood(state);
    features[2] = NumFood(state);

    double value = 0;
    for(int i = 0, size = features.size(); i<size; i++){
	value +=features[i]*coeff[i];
    }
    return value;
}


double Utility::PacmanToGhostDistance(const State &state) const{
    double value = 0;
    for(int i = 0; i <state.NumGhost(); i++){
	double dis = Position::Manhattan(state.PacmanPosition(), 
					 state.GhostPosition(i));
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

