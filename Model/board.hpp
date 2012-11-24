#ifndef BOARD_HPP
#define BOARD_HPP

#include "cell.hpp"
#include "position.hpp"
#include <iostream>

using namespace std;

class Board{
private:
    vector<Cell> m;
    int rows, cols;
    Pacman 
public:
    Board(int rows, int cols);
    int Rows() const;
    int Cols() const;
    void Init();

    struct Position PacmanPos() const;
    struct Position GhostPos() const;

    Cell operator()(int i, int j) const;
    Cell &operator()(int i, int j);
    Cell operator()(int i) const;
    Cell &operator()(int i);

    void MovePacman()
    
};

#endif
