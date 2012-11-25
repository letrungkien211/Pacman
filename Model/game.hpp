#ifndef GAME_HPP
#define GAME_HPP

#include "cell.hpp"
#include "common.hpp"
#include <iostream>
#include <vector>

#define MAXTURN 1
#define MINTURN -1

using namespace std;
 
class Game{
private:
    vector<Cell> m;
    int rows, cols;
    int turn;
    Position pacmanPos;
    Position ghostPos;
    int numFood;
    Result res;
public:
    Game(int rows, int cols);
    void Init(); // Initilize
    Game ApplyAction(Action action); // Apply an action
    Result Res() const; // Check if the game is ended
    bool IsLegalAction(Action action) const;
    vector<Action> GetLegalAction() const;
    double Evaluate() const;
    /*Element Access*/
    Cell operator()(int i, int j) const;
    Cell &operator()(int i, int j);
    Cell operator()(int i) const;
    Cell &operator()(int i);
    Position PacmanPosition() const;
    Position GhostPosition() const;
    int NumFood() const;
    int Turn() const;
    int Rows() const;
    int Cols() const;
    
};
ostream & operator<<(ostream &os, const Game& game);

#endif
