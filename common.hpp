#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>
#include <vector>
using namespace std;

#define INFINITY 1000000
#define MAXTURN 0
#define MINTURN 1
#define SCARETIMOUT 10


enum Action{
    STOP = 'S', 
    UP = 'U',
    DOWN = 'D',
    LEFT = 'L',
    RIGHT ='R'
};

bool IsOppositeAction(Action a, Action b);
bool InRange(int i, int j, int rows, int cols);
bool InRange(int i, int min, int max);
Action Char2Action(char c);
char Action2Char(Action action);
enum Result{
    LOSE, WIN, UNKOWN
};

ostream &operator<<(ostream &os, Action action);
ostream &operator<<(ostream &os, Result result);
ostream &operator<<(ostream &os, vector<Action> &action);

class Position{
public:
    int row ;
    int col ;
    Position(int row, int col);
    Position();
    void Move(Action action);
    bool IsLegal(Action action, int rows, int cols) const;
    int ToIndex(int cols) const;
    bool operator==(Position &other) const;
    bool Equal(Position pos) const;
    bool Equal(int i, int j) const;
    static double Manhattan(const Position& p, const Position & q);

};

ostream &operator<<(ostream &os, Position pos);

#endif
