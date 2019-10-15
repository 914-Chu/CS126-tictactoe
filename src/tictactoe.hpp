#pragma once
#include <string>

using namespace std;

enum class Evaluation {
    InvalidInput,
    NoWinner,
    Xwins,
    Owins,
    UnreachableState
};

class TicTacToe {

private:
    char winner;
    int winCount,
        XCount,
        OCount;

public:
    TicTacToe();
    ~TicTacToe();
    Evaluation EvaluateBoard(const string &board_state);

};



// Put other methods, enums, classes, etc. declarations here

