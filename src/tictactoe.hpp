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
    TicTacToe(): winCount(0), XCount(0), OCount(0) {};
    ~TicTacToe() {};
    Evaluation EvaluateBoard(const string &board_state);
    string& trim(const string &str);
    void count(const string &str);
    int getXCount();
    int getOCount();
};



// Put other methods, enums, classes, etc. declarations here

