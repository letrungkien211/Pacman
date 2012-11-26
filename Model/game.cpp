#ifndef GAME_HPP
#define GAME_HPP

class Game:public State{
private:
  // Static wall matrix
  vector<bool> wall;
  // Score
  int score;

public:
  Game();
  Game(int rows, int cols, bool wall[]);
  void Initialize(int rows, int cols, bool wall[]);
};

#endif
