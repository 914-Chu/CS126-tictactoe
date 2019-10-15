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
    const int BOARD_CAPACITY = 9;
    const int ROW = 3;
    const int COL = 3;
    int winCount,
        XCount,
        OCount;
    bool

public:
    TicTacToe(): winCount(0), XCount(0), OCount(0) {};
    ~TicTacToe() {};
    Evaluation EvaluateBoard(const string &board_state);
    string trim(const string &str);
    void count(const string &str);
    char** setUpBoard(const string &str);
    bool isFull();
    bool hasBalanceTurn();
    bool hadWinner(char** board);
    int getXCount();
    int getOCount();
};



// Put other methods, enums, classes, etc. declarations here

