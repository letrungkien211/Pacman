#ifndef CELL_HPP
#define CELL_HPP

using namespace std;

class Cell{
private:
    int  food;
    bool wall;
public:
    Cell();
    bool Wall() const;
    void SetWall(bool wall);
    int Food() const;
    void SetFood(int food);
};

#endif
