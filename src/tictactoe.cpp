#include "tictactoe.hpp"
#include<algorithm>
#include<cmath>
#include<vector>

using namespace std;

Evaluation TicTacToe::EvaluateBoard(const string &board_state) {

    string boardState = board_state;
    boardState = Trim(boardState);
    transform(boardState.begin(), boardState.end(), boardState.begin(), ::tolower);

    if (boardState.empty() || boardState.length() != static_cast<unsigned int>(kBOARD_CAPACITY)) {
        return Evaluation::InvalidInput;
    } else {
        vector<vector<char>>board = SetUpBoard(boardState);
        winCount = 0;
        vector<char> rowState = CheckRow(board);
        vector<char> colState = CheckCol(board);
        vector<char> diagonalState = CheckDiagonal(board);

        if ((winCount > 1 && HasInvalidTwoLine(rowState, colState, diagonalState)) || !HasBalanceTurn(boardState)) {
            return Evaluation::UnreachableState;
        }else if (IsEmptyBoard(board) || winCount == 0) {
            return Evaluation::NoWinner;
        } else if(winner == 'x'){
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

    vector<vector<char>> board( kSIDE_LENGTH , vector<char> (kSIDE_LENGTH, '.'));
    for(unsigned int row = 0; row < kSIDE_LENGTH; row++){
        for(unsigned int col = 0; col < kSIDE_LENGTH; col++){
            char character = str[static_cast<unsigned int>(kSIDE_LENGTH * row + col)];
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

    vector<char> state(kSIDE_LENGTH);
    for(unsigned int row = 0; row < kSIDE_LENGTH; row++){
        bool equal = true;
        if(IsXorO(board[row][kFIRST])) {
            for (unsigned int col = 0; col < kSIDE_LENGTH - 1; col++) {
                if (board[row][col] != board[row][col + 1]) {
                    equal = false;
                    break;
                }
            }
            if (equal) {
                winner = board[row][kFIRST];
                state[row] = winner;
                winCount++;
            }
        }
    }
    return state;
}

vector<char> TicTacToe::CheckCol(vector<vector<char>> board){

    vector<char> state(kSIDE_LENGTH);
    for(unsigned int col = 0; col < kSIDE_LENGTH; col++){
        bool equal = true;
        if(IsXorO(board[kFIRST][col])) {
            for (unsigned int row = 0; row < kSIDE_LENGTH - 1; row++) {
                if (board[row][col] != board[row + 1][col]) {
                    equal = false;
                    break;
                }
            }
            if (equal) {
                winner = board[kFIRST][col];
                state[col] = winner;
                winCount++;
            }
        }
    }
    return state;
}

vector<char> TicTacToe::CheckDiagonal(vector<vector<char>> board){

    vector<char> state(kSIDE_LENGTH);
    bool equal = true;
    if(IsXorO(board[kFIRST][kFIRST])) {
        for (unsigned int row = 0; row < kSIDE_LENGTH - 1; row++) {
            unsigned int col = row;
            if (board[row][col] != board[row + 1][col + 1]) {
                equal = false;
                break;
            }
        }
        if (equal) {
            winner = board[kFIRST][kFIRST];
            state[kBACKWARD] = winner;
            winCount++;
        }
    }

    equal = true;
    if(IsXorO(board[kFIRST][kLAST])) {
        for (unsigned int row = 0; row < kSIDE_LENGTH - 1; row++) {
            unsigned int col = kLAST - row;
            if (board[row][col] != board[row + 1][col - 1]) {
                equal = false;
                break;
            }
        }
        if (equal) {
            winner = board[kFIRST][kLAST];
            state[kFORWARD] = winner;
            winCount++;
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

    for(unsigned int row = 0; row < kSIDE_LENGTH; row++){
        for(unsigned int col = 0; col < kSIDE_LENGTH; col++){
            if(IsXorO(board[row][col])){
                return false;
            }
        }
    }
    return true;
}




