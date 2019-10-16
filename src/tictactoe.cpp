#include "tictactoe.hpp"
#include<algorithm>
#include<cmath>
#include<vector>

using namespace std;

Evaluation TicTacToe::EvaluateBoard(const string &board_state) {
    string boardState = board_state;
    boardState = Trim(boardState);
    transform(boardState.begin(), boardState.end(), boardState.begin(), ::tolower);

    if (boardState.empty() || boardState.length() != static_cast<unsigned int>(kBoardCapacity)) {
        return Evaluation::InvalidInput;
    } else {
        win_count_ = 0;
        vector<vector<char>>board = SetUpBoard(boardState);
        vector<char> rowState = CheckRow(board);
        vector<char> colState = CheckCol(board);
        vector<char> diagonalState = CheckDiagonal(board);

        if ((win_count_ > 1 && HasInvalidTwoLine(rowState, colState, diagonalState)) || !HasBalanceTurn(boardState)) {
            return Evaluation::UnreachableState;
        }else if (IsEmptyBoard(board) || win_count_ == 0) {
            return Evaluation::NoWinner;
        } else if(winner_ == 'x'){
                return Evaluation ::Xwins;
        }else{
                return Evaluation::Owins;
        }
    }
}

string TicTacToe::Trim(const string &str) {
    if (str.empty()) {
        return str;
    }
    string unTrim = str;
    unTrim.erase(0,unTrim.find_first_not_of(' '));
    unTrim.erase(unTrim.find_last_not_of(' ') + 1);
    return unTrim;
}

vector<vector<char>> TicTacToe::SetUpBoard(const string &str){
    vector<vector<char>> board( kSideLength , vector<char> (kSideLength, '.'));
    for(unsigned int row = 0; row < kSideLength; row++){
        for(unsigned int col = 0; col < kSideLength; col++){
            char character = str[static_cast<unsigned int>(kSideLength * row + col)];
            if(IsXorO(character)){
                board[row][col] = character;
            }
        }
    }

    return board;
}

bool TicTacToe::HasBalanceTurn(const string &str) {
    int XCount = 0;
    int OCount = 0;

    for(char character : str) {
        if(character == 'x'){
            XCount++;
        }else if(character == 'o'){
            OCount++;
        }
    }
    return abs(XCount - OCount) < 2;
}

vector<char> TicTacToe::CheckRow(vector<vector<char>>board){
    vector<char> state(kSideLength);
    for(unsigned int row = 0; row < kSideLength; row++){
        bool equal = true;
        if(IsXorO(board[row][kFirst])) {
            for (unsigned int col = 0; col < kSideLength - 1; col++) {
                if (board[row][col] != board[row][col + 1]) {
                    equal = false;
                    break;
                }
            }
            if (equal) {
                winner_ = board[row][kFirst];
                state[row] = winner_;
                win_count_++;
            }
        }
    }
    return state;
}

vector<char> TicTacToe::CheckCol(vector<vector<char>> board){
    vector<char> state(kSideLength);
    for(unsigned int col = 0; col < kSideLength; col++){
        bool equal = true;
        if(IsXorO(board[kFirst][col])) {
            for (unsigned int row = 0; row < kSideLength - 1; row++) {
                if (board[row][col] != board[row + 1][col]) {
                    equal = false;
                    break;
                }
            }
            if (equal) {
                winner_ = board[kFirst][col];
                state[col] = winner_;
                win_count_++;
            }
        }
    }
    return state;
}

vector<char> TicTacToe::CheckDiagonal(vector<vector<char>> board){
    vector<char> state(kSideLength);
    bool equal = true;
    if(IsXorO(board[kFirst][kFirst])) {
        for (unsigned int row = 0; row < kSideLength - 1; row++) {
            unsigned int col = row;
            if (board[row][col] != board[row + 1][col + 1]) {
                equal = false;
                break;
            }
        }
        if (equal) {
            winner_ = board[kFirst][kFirst];
            state[kBackward] = winner_;
            win_count_++;
        }
    }

    equal = true;
    if(IsXorO(board[kFirst][kLast])) {
        for (unsigned int row = 0; row < kSideLength - 1; row++) {
            unsigned int col = kLast - row;
            if (board[row][col] != board[row + 1][col - 1]) {
                equal = false;
                break;
            }
        }
        if (equal) {
            winner_ = board[kFirst][kLast];
            state[kForward] = winner_;
            win_count_++;
        }
    }
    return state;
}

bool TicTacToe::HasInvalidTwoLine(vector<char> rowState, vector<char> colState, vector<char> diagonalState) {

    return (HasWinner(rowState) != HasWinner(colState)) && !HasWinner(diagonalState);
}

bool TicTacToe::HasWinner(vector<char> state) {
    for(char character : state){
        if(IsXorO(character)){
            return true;
        }
    }
    return false;
}

bool TicTacToe::IsXorO(char character){
    return character == 'x' || character == 'o';
}

bool TicTacToe::IsEmptyBoard(vector<vector<char>> board) {
    for(unsigned int row = 0; row < kSideLength; row++){
        for(unsigned int col = 0; col < kSideLength; col++){
            if(IsXorO(board[row][col])){
                return false;
            }
        }
    }
    return true;
}




