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
        char** board = SetUpBoard(boardState);
        vector<vector<char>>boards = SetUpBoard(boardState);
        winCount = 0;
        char *rowState = CheckRow(board);
        char *colState = CheckCol(board);
        char *diagonalState = CheckDiagonal(board);

        if ((winCount > 1 && HasInvalidTwoLine(rowState,colState, diagonalState)) || !HasBalanceTurn(boardState)) {
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

char** TicTacToe::SetUpBoard(const string &str){

    vector<vector<char>> board( kSIDE_LENGTH , vector<char> (kSIDE_LENGTH, '.'));
    for(int row = 0; row < kSIDE_LENGTH; row++){
        for(int col = 0; col < kSIDE_LENGTH; col++){
            char character = str[static_cast<unsigned int>(kSIDE_LENGTH * row + col)];
            if(IsXorO(character)){
                board[row][col] = character;
            }
        }
    }

    char** board = new char* [kSIDE_LENGTH];
    for(int row = 0; row < kSIDE_LENGTH; row++){
        board[row] = new char [kSIDE_LENGTH];
        for(int col = 0; col < kSIDE_LENGTH; col++){
            char character = str[static_cast<unsigned int>(kSIDE_LENGTH * row + col)];
            if(!IsXorO(character)){
                character = '.';
            }
            board[row][col] = character;
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

char* TicTacToe::CheckRow(char** board){

    char* state = new char[kSIDE_LENGTH];
    for(int row = 0; row < kSIDE_LENGTH; row++){
        bool equal = true;
        if(IsXorO(board[row][kFIRST])) {
            for (int col = 0; col < kSIDE_LENGTH - 1; col++) {
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

char* TicTacToe::CheckCol(char** board){

    char* state = new char[kSIDE_LENGTH];
    for(int col = 0; col < kSIDE_LENGTH; col++){
        bool equal = true;
        if(IsXorO(board[kFIRST][col])) {
            for (int row = 0; row < kSIDE_LENGTH - 1; row++) {
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

char* TicTacToe::CheckDiagonal(char** board){

    char* state = new char[kDIAGONAL_AMOUNT];
    bool equal = true;
    if(IsXorO(board[kFIRST][kFIRST])) {
        for (int row = 0; row < kSIDE_LENGTH - 1; row++) {
            int col = row;
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
        for (int row = 0; row < kSIDE_LENGTH - 1; row++) {
            int col = kLAST - row;
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

bool TicTacToe::HasInvalidTwoLine(char* rowState, char* colState, char* diagonalState) {

    return (HasWinner(rowState) != HasWinner(colState)) && !HasWinner(diagonalState);
}

bool TicTacToe::HasWinner(char* state) {

    int size = sizeof(state)/sizeof(*state);
    for(int i = 0; i< size; i++){
        if(IsXorO(state[i])){
            return true;
        }
    }
    return false;
}

bool TicTacToe::IsXorO(char character){
    return character == 'x' || character == 'o';
}

bool TicTacToe::IsEmptyBoard(char** board) {

    for(int row = 0; row < kSIDE_LENGTH; row++){
        for(int col = 0; col < kSIDE_LENGTH; col++){
            if(IsXorO(board[row][col])){
                return false;
            }
        }
    }
    return true;
}




