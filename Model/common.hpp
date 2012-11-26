#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>
#include <limits>
using namespace std;

#define INFINITY 1000000
#define MAXTURN 0
#define MINTURN 1

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

enum Result{
    LOSE, WIN, UNKOWN
};

ostream &operator<<(ostream &os, Action action);
ostream &operator<<(ostream &os, Result result);

class Position{
public:
    int row ;
    int col ;
    void Move(Action action);
    bool IsLegal(Action action, int rows, int cols) const;
  bool Equal(Position pos);
  bool Equal(int i, int j);
    static double Manhattan(const Position& p, const Position & q);

};

#endif
