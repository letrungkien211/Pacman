#include <iostream>
#include <cstdio>
#include <cctype>
#include "minimaxAgent.hpp"

using namespace std;



int initFood[] ={10,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,
		 1,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,1,
		 1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
		 1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,
		 1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,
		 1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,1,
		 1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
		 1,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,1,
		 1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,10};
		 
bool initWall[] ={0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0, // 0
		  0,1,1,0,1,0,1,1,1,1,1,1,0,1,0,1,1,0,  // 1
		  0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0, 
		  0,1,0,1,1,0,1,1,0,0,1,1,0,1,1,0,1,0, 
		  0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0, // 5
		  0,1,0,1,1,0,1,1,1,1,1,1,0,1,1,0,1,0, 
		  0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0, 
		  0,1,1,0,1,0,1,1,1,1,1,1,0,1,0,1,1,0,  // 1
		  0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0};

int main(int argc, char **argv){
    State state(9,18,initWall, initFood);
    MinimaxAgent minimax;
    
    vector<double> coeff(NUMFEATURES);
    coeff[0] = 10;
    coeff[1] = 3;
    coeff[2] = -1;
    coeff[3] = -1;
    coeff[4] = 1000;
    minimax.SetCoeff(coeff);

    minimax.PreCalculateMinDistance(&state);

    int cnt  = 0;
    while(state.IsFinal() == UNKOWN ){
    	cout << "Turn #" <<cnt++ <<endl;
    	cout << state <<endl;
    	double v;
    	vector<Action> combinedAction = minimax.ChooseCombinedGhostAction(state, 9,&v);
    	Action pacmanAction;
	do{
	    string str;
	    cin >> str;
	    pacmanAction = Char2Action(str[0]);
	}
	while(!state.IsLegalPacmanAction(pacmanAction));
    	state.GetNextState(pacmanAction, combinedAction);
    	cout << "Ghost Minimax Move: " << combinedAction<< endl;
    }
    cout << "Pacman " << state.IsFinal() << endl;
    
    state.Finalize();
    return 0;
}
