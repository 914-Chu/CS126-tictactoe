#pragma once
#include <string>
#include <vector>

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
    const unsigned int kBOARD_CAPACITY = 9;
    const unsigned int kSIDE_LENGTH = 3;
    const unsigned int kDIAGONAL_AMOUNT = 2;
    const unsigned int kFORWARD = 0;
    const unsigned int kBACKWARD = 1;
    const unsigned int kFIRST = 0;
    const unsigned int kLAST = kSIDE_LENGTH - 1;
    int winCount;
    char winner;

public:
    TicTacToe() {};
    ~TicTacToe() {};
    Evaluation EvaluateBoard(const string&);
    string Trim(const string&);
    vector<char> CheckRow(vector<vector<char>>);
    vector<char> CheckCol(vector<vector<char>>);
    vector<char> CheckDiagonal(vector<vector<char>>);
    vector<vector<char>> SetUpBoard(const string&);
    bool IsXorO(char);
    bool IsEmptyBoard(vector<vector<char>>);
    bool HasBalanceTurn(const string&);
    bool HasInvalidTwoLine(vector<char>,vector<char>,vector<char>);
    bool HasWinner(vector<char>);
};
