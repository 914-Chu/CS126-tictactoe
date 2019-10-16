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
    const unsigned int kBoardCapacity = 9;
    const unsigned int kSideLength = 3;
    const unsigned int kForward = 0;
    const unsigned int kBackward = 1;
    const unsigned int kFirst = 0;
    const unsigned int kLast = kSideLength - 1;
    int win_count_;
    char winner_;

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
