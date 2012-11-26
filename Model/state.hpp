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
    // Static wall matrix
    static vector<bool> wall;
    // Turn 
    int turn;     
    // Number of food
    int numFood;    
    // Static number of rows, cols
    static int rows;
    static int cols;
    // Score
    int score;
    // Number of actions taken
    int numAction;
    // Pacman position
    Position pacmanPos;
    // Ghosts' position
    vector<Position> ghostPos;
    // Previous ghost actions
    vector<Action> previousGhostAction;
    // Gostscared
    vector<int> ghostScared;
    // Make ghost scared
    void MakeGhostScared(bool scared);
public:
    // Constructor
    State();
    State(int[] food);
    // Static initialization
    static void Initialize(int rows, int cols, int[] mWall);
    // Initialization
    void Initialize(int[] food); // Initilize
    
    // Get next states
    State GetNextState(Action pacmanAction, vector<Action> ghostAction);
    State GetNextState(Action pacmanAction);
    State GetNextState(vector<Action> ghostAction);

    // Get legal actions
    vector<Action > GetLegalGhostAction(int ghostIndex) const;
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
    int Turn() const;
    int NumFood() const;
    int NumAction() const;
    Result IsFinal() const; // Check if the State is ended
    bool GhostScared() const;
    int Rows() const;
    int Cols() const;
    int Score() const;
    int NumGhost() const;
    Position PacmanPosition();
    Position GhostPosition(int ghostIndex);
};

ostream & operator<<(ostream &os, const State& state);
#endif
