#include <iostream>
#include <cstdio>

#include "minimaxAgent.hpp"

using namespace std;


int initFood[] ={1,1,1,1,1,1,1,1,
		 1,0,0,0,0,0,0,1,
		 1,1,1,1,1,1,1,1,
		 1,0,0,0,0,0,0,1,
		 1,0,0,0,0,0,0,1,
		 1,0,0,0,0,0,0,1,
		 1,1,1,1,1,1,1,1,
		 1,0,0,0,0,0,0,1,
		 1,1,1,1,1,1,1,1};
		 
bool initWall[] ={0,0,0,0,0,0,0,0,
		 0,1,0,1,1,1,1,0,
		 0,0,0,0,0,0,0,0,
		 0,1,1,0,0,1,1,0,
		 0,1,0,0,0,0,1,0,
		 0,1,1,1,1,1,1,0,
		 0,0,0,0,0,0,0,0,
		 0,1,1,1,1,1,1,0,
		 0,0,0,0,0,0,0,0};




int main(int argc, char **argv){
  State::Initialize(9,8, initWall);
  State state(initFood);
  cout << state <<endl;
  state.GetNextState(UP);
  cout << state <<endl;
  state.GetNextState(UP);
  cout << state <<endl;
  state.GetNextState(UP);
  cout << state <<endl;
  state.GetNextState(UP);
  cout << state <<endl;
  state.GetNextState(UP);
  cout << state <<endl;
  return 0;
}


