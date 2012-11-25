#include <iostream>
#include <cstdio>

#include "minimaxAgent.hpp"

using namespace std;



int main1(int argc, char **argv){
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


int main(int argc, char **argv){
    Game game(5,5);
    MinimaxAgent minimax;
    game.Init();

    int cnt = 0;
    while(game.Res()==UNKOWN){
	cout << cnt++ << " -----------------------------------" <<endl;
	cout << game <<endl;
	Action action = minimax.GetAction(game,1);
	cout << "Best action: " << action<<endl;
	game.ApplyAction(action);
	getchar();
    }

    return 0;
}
