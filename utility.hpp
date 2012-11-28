#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <utility>
#include <vector>
#include <map>
#include "state.hpp"

using namespace std;

#define NUMFEATURES 7

class Utility{
protected:
    vector<double> coeff;
    vector<vector<string> > shortestPath;
public:
    Utility();
    Utility(const vector<double> &coeff);
    void SetCoeff(const vector<double> &coeff);

    void PreCalculateMinDistance(State *state);
    string PreCalculateMinDistance(State *state, int start, int goal);
    double Evaluate(const State &state);
    // Features
    double PacmanToGhostDistance(const State &state) const;
    double PacmanToNearestFood(const State &state) const;
    double NumFood(const State &state) const;
    double GhostToGhostDistance(const State &state) const;
    double IsFinal(const State &state) const;
    double NumGhostKilled(const State &state) const;
    double GhostDirection(const State&state) const;
};
#endif
