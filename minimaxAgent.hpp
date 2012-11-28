#ifndef MINIMAXAGENT_HPP
#define MINIMAXAGENT_HPP

#include "utility.hpp"
#include <iostream>
#include <vector>

using namespace std;

class MinimaxAgent:public Utility{
public:
    virtual double Evaluate(const State &state, int depth, int player);
    Action ChoosePacmanAction(const State &state, int depth, double *v =NULL);
    vector<Action> ChooseCombinedGhostAction(const State &state, int depth, double *v=NULL);
};

#endif
