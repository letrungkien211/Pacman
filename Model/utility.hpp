#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <vector>
#include "state.hpp"

using namespace std;

class Utility{
private:
    vector<double> coeff;
public:
    Utility();
    Utility(const vector<double> &coeff);
    void SetCoeff(const vector<double> &coeff);
    double Evaluate(const State &state);

    // Features
    double PacmanToGhostDistance(const State &state) const;
    double PacmanToNearestFood(const State &state) const;
    double NumFood(const State &state) const;
};
#endif
