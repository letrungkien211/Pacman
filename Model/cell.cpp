#include "cell.hpp"

Cell::Cell(){
    hasFood = false;
    isWall = false;
}

bool Cell::IsWall(){
    return isWall;
}

bool Cell::HasFood(){
    return hasFood;
}

void Cell::SetFood(bool hasFood){
    this->hasFood = hasFood;
}

void Cell::SetWall(bool isWall){
    this->isWall = isWall;
}
