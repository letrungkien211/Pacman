#ifndef STATE_HPP
#define STATE_HPP

#include "common.hpp"
#include <iostream>
#include <vector>

using namespace std;
 
class State{
private:
    // Food matrix
    vector<int> food;
    // Wall matrix
    bool *wall;
    // Number of rows, cols
    int rows, cols;
    // Number of food
    int numFood;
    // Number of move
    int startScared;
    int numMove;
    // Pacman's position
    Position pacmanPos;
    // Ghosts' position
    vector<Position> ghostPos;
    // Previous ghost actions
    vector<Action> previousGhostAction;
    // Gostscared
    vector<bool> ghostScared;
    // Make ghost scared
    void MakeGhostScared(bool scared);
public:
    // Constructor
    State();
    State(int rows, int cols, bool *wall, int *food);
    // Initialization
    void Initialize(int rows, int cols, bool *wall, int *food);
    // Get next states
    State GetNextState(Action pacmanAction, const vector<Action> &ghostAction);
    State GetNextState(Action pacmanAction);
    State GetNextState(const vector<Action> &ghostAction);
    // Get legal actions
    vector<Action > GetLegalGhostAction(int ghostIndex) const;
    vector<vector<Action> > GetLegalCombinedGhostAction(int ghostIndex) const;
    vector<vector<Action> > GetLegalCombinedGhostAction() const;
    vector<Action > GetLegalPacmanAction() const;
    // Check if legal actions
    bool IsLegalPacmanAction(Action pacmanAction) const;
    bool IsLegalGhostAction(Action ghostAction, int ghostIndex) const;
    bool IsLegalCombinedGhostAction(vector<Action> ghostAction) const;
    /*Element Access*/
    int Food(int i, int j) const;
    int &Food(int i, int j);
    int Food(Position pos) const;
    int &Food(Position pos);
    bool Wall(int i, int j) const;
    bool Wall(Position pos) const;
    bool Wall(int i) const;
    int NumFood() const;
    int NumAction() const;
    Result IsFinal() const; 
    int Rows() const;
    int Cols() const;
    int NumGhost() const;
    int GhostScared(int ghostIndex) const;
    bool GhostKilled(int ghostIndex) const;
    Position PacmanPosition() const;
    Position GhostPosition(int ghostIndex) const;
    Action PreviousGhostAction(int ghostIndex) const;
    void IncrementNumMove();
    int NumMove() const;
};

ostream & operator<<(ostream &os, const State& state);
void GameDraw(const State& state);
#endif
