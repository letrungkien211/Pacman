#ifndef CELL_HPP
#define CELL_HPP

using namespace std;

class Cell{
private:
    bool hasFood;
    bool isWall;
public:
    Cell();
    bool IsWall() const;
    void SetWall(bool hasWall);
    bool HasFood() const;
    void SetFood(bool hasFood);

};

#endif
