#include "cell.hpp"

Cell::Cell(){
    isFood = false;
    isWall = false;
}

bool Cell::IsWall() const{
    return isWall;
}

bool Cell::IsFood() const{
    return isFood;
}

void Cell::SetFood(bool isFood){
    this->isFood = isFood;
}

void Cell::SetWall(bool isWall){
    this->isWall = isWall;
}
