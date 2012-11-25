#ifndef MINIMAXAGENT_HPP
#define MINIMAXAGENT_HPP

#include "game.hpp"
#include <iostream>
#include <vector>

using namespace std;

class MinimaxAgent{
public:
    double Evaluate(const Game &game, int depth = 0);
    double GetAction(const Game &game, int depth);
};
ostream & operator<<(ostream &os, const Game& game);

#endif
