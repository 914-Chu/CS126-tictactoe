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
    const int SIZE = 3;
    const int DIAGONAL = 2;
    const int FORWARD = 0;
    const int BACKWARD = 1;
    const int FIRST = 0;
    const int LAST = SIZE - 1;
    int winCount,
        XCount,
        OCount;
    char* rowState;
    char* colState;
    char* diagonalState;

public:
    TicTacToe(): winCount(0), XCount(0), OCount(0) {};
    ~TicTacToe() {};
    Evaluation EvaluateBoard(const string&);
    string trim(const string&);
    void count(const string&);
    char* checkRow(char**);
    char* checkCol(char**);
    char* checkDiagonal(char**);
    char** setUpBoard(const string&);
    bool isXorO(char);
    bool isFull(int, int);
    bool isEmptyBoard(char**);
    bool hasBalanceTurn(int, int);
    bool hasValidTwoLine();
    bool hadWinner();
    int getXCount();
    int getOCount();
};



// Put other methods, enums, classes, etc. declarations here

