#ifndef GAME_HPP
#define GAME_HPP

class Game{
private:
    vector<bool> wall;
    
public:
    // Get next state
    State GetNextState(const State &state, Action pacmanAction, const vector<Action> &ghostAction);
    State GetNextState(const State &state, Action pacmanAction);
    State GetNextState(const State &state, const vector<Action> &ghostAction);

    // Get legal actions
    vector<Action > GetLegalGhostAction(const State &state, int ghostIndex) const;
    vector<vector<Action> > GetLegalCombinedGhostAction(const State &state, int ghostIndex = 0) const;
    vector<Action > GetLegalPacmanAction(const State &state) const;
    
    // Check if legal actions
    bool IsLegalPacmanAction(const State& state, Action pacmanAction) const;
    bool IsLegalGhostAction(const State& state, Action ghostAction, int ghostIndex) const;
    bool IsLegalCombinedGhostAction(const State &state, vector<Action> ghostAction) const;


    bool Wall(int i, int j) const;
    bool Wall(Position pos) const;
};

#endif
