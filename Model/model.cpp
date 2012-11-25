#include <iostream>
#include <cstdio>

#include "minimaxAgent.hpp"

using namespace std;

int main(int argc, char **argv){
    Game game(5,5);
    game.Init();
    cout << game <<endl;
    game.ApplyAction(UP);
    cout << game <<endl;
    game.ApplyAction(UP);
    cout << game <<endl;
    game.ApplyAction(UP);
    cout << game <<endl;
    game.ApplyAction(UP);
    cout << game <<endl;
    game.ApplyAction(UP);
    cout << game <<endl;
    
    vector<Action> actions = game.GetLegalAction();
    for(unsigned int i = 0; i< actions.size(); i++)
	cout << actions[i] << " ";

    return 0;
}
