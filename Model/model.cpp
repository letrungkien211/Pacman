#include <iostream>
#include <cstdio>

#include "minimaxAgent.hpp"

using namespace std;



int main1(int argc, char **argv){
    Game game(10,10);
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
    Game game(9,8);
    MinimaxAgent minimax;
    game.Init();

    int cnt = 0;
    do{
	cout << cnt++ << " -----------------------------------" <<endl;
	cout << game <<endl;
	Action action = minimax.GetAction(game,3);
	cout << "Best action: " << action<<endl;
	game.ApplyAction(action);
	getchar();
    }while(game.Res()==UNKOWN);
	cout << game <<endl;
    return 0;
}
