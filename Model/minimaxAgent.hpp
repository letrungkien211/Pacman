#ifndef MINIMAXAGENT_HPP
#define MINIMAXAGENT_HPP

#include "utility.hpp"
#include <iostream>
#include <vector>

using namespace std;

class MinimaxAgent:public Utility{
public:
    double Evaluate(const State &state, int depth);
    Action ChoosePacmanAction(const State &state, int depth);
    vector<Action> ChooseCombinedGhostAction(const State &state, int depth);
};

#endif
