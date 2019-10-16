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
    const int kBOARD_CAPACITY = 9;
    const int kSIDE_LENGTH = 3;
    const int kDIAGONAL_AMOUNT = 2;
    const int kFORWARD = 0;
    const int kBACKWARD = 1;
    const int kFIRST = 0;
    const int kLAST = kSIDE_LENGTH - 1;
    int winCount;
    char winner;

public:
    TicTacToe() {};
    ~TicTacToe() {};
    Evaluation EvaluateBoard(const string&);
    string Trim(const string&);
    char* CheckRow(char**);
    char* CheckCol(char**);
    char* CheckDiagonal(char**);
    char** SetUpBoard(const string&);
    bool IsXorO(char);
    bool IsEmptyBoard(char**);
    bool HasBalanceTurn(const string&);
    bool HasInvalidTwoLine(char*, char*, char*);
    bool HasWinner(char*);
};



// Put other methods, enums, classes, etc. declarations here

