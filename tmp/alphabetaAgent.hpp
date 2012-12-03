#ifndef ALPHABETAAGENT_HPP
#define ALPHABETAAGENT_HPP

#include "minimaxAgent.hpp"

class AlphaBetaAgent:public MinimaxAgent{
public:
    virtual double Evaluate(const State &state, int depth, int player);
    double Evaluate(const State &state, int depth, int player, double alpha, double beta);
};

#endif
