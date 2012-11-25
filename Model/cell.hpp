#ifndef CELL_HPP
#define CELL_HPP

using namespace std;

class Cell{
private:
    bool isFood;
    bool isWall;
public:
    Cell();
    bool IsWall() const;
    void SetWall(bool hasWall);
    bool IsFood() const;
    void SetFood(bool isFood);

};

#endif
