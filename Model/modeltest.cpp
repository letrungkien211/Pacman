#include <iostream>
#include <cstdio>

#include "board.hpp"


using namespace std;

int main(int argc, char *argv[]){
    Board board(5,5);
    board.Init();
    cout << board<<endl;
    return 0;
}
