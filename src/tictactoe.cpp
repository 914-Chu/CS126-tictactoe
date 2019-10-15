#include "tictactoe.hpp"
#include<algorithm>
#include<cmath>

using namespace std;

Evaluation TicTacToe::EvaluateBoard(const string &board_state) {

    string boardState = board_state;
    boardState = trim(boardState);
    transform(boardState.begin(), boardState.end(), boardState.begin(), ::tolower);
    count(boardState);

    if (boardState.empty() || boardState.length() != BOARD_CAPACITY) {
        return Evaluation::InvalidInput;
    } else {
        char** board = setUpBoard(boardState);
        rowState = checkRow(board);
        colState = checkCol(board);
        diagonalState = checkDiagonal(board);

        if (hadWinner() || !hasBalanceTurn(XCount, OCount)) {
            return Evaluation::UnreachableState;
        }else if (isEmptyBoard(board) || winCount == 0) {
            return Evaluation::NoWinner;
        } else {
            
        }
    }
}

string TicTacToe::trim(const string &str) {

    if (str.empty()) {
        return str;
    }

    string unTrim = str;
    unTrim.erase(0,unTrim.find_first_not_of(' '));
    unTrim.erase(unTrim.find_last_not_of(' ') + 1);
    return unTrim;
}

void TicTacToe::count(const string &str) {

    for(char character : str) {
        if(character == 'x'){
            XCount++;
        }else if(character == 'o'){
            OCount++;
        }
    }
}

char** TicTacToe::setUpBoard(const string &str){

    char** board = new char* [SIZE];
    for(int row = 0; row < SIZE; row++){
        board[row] = new char [SIZE];
        for(int col = 0; col < SIZE; col++){
            char character = str[SIZE*row + col];
            if(!isXorO(character)){
                character = '.';
            }
            board[row][col] = character;
        }
    }
    return board;
}

bool TicTacToe::isFull(int XCount, int OCount) {
    return XCount + OCount == BOARD_CAPACITY;
}

bool TicTacToe::hasBalanceTurn(int XCount, int OCount) {
    return abs(XCount - OCount) < 2;
}

char* TicTacToe::checkRow(char** board){

    char state[SIZE];
    for(int row = 0; row < SIZE; row++){
        bool equal = true;
        for(int col = 0; col < SIZE-1; col++){
            if(board[row][col] != board[row][col+1]){
                equal = false;
                break;
            }
        }
        if(equal){
            state[row] = board[row][FIRST];
            winCount++;
        }
    }
    return state;
}

char* TicTacToe::checkCol(char** board){

    char state[SIZE];
    for(int col = 0; col < SIZE; col++){
        bool equal = true;
        for(int row = 0; row < SIZE-1; row++){
            if(board[row][col] != board[row+1][col]){
                equal = false;
                break;
            }
        }
        if(equal){
            state[col] = board[FIRST][col];
            winCount++;
        }
    }
    return state;
}

char* TicTacToe::checkDiagonal(char** board){

    char state[DIAGONAL];
    bool equal = true;
    for(int row = 0; row < SIZE-1; row++){
        int col = row;
        if(board[row][col] != board[row+1][col+1]){
            equal = false;
            break;
        }
    }
    if(equal){
        state[BACKWARD] = board[FIRST][FIRST];
        winCount++;
    }
    equal = true;
    for(int row = 0; row < SIZE-1; row++){
        int col = LAST - row;
        if(board[row][col] != board[row+1][col-1]){
            equal = false;
            break;
        }
    }
    if(equal){
        state[FORWARD] = board[FIRST][LAST];
        winCount++;
    }
    return state;
}

bool TicTacToe::hadWinner() {
    return winCount > 1 && !hasValidTwoLine();
}

bool TicTacToe::hasValidTwoLine() {

    return (isXorO(rowState[FIRST]) && (rowState[FIRST] == colState[FIRST] || rowState[FIRST] == colState[LAST]))
           || (isXorO(rowState[LAST]) && (rowState[LAST] == colState[FIRST] || rowState[LAST] == colState[LAST]))
           || (isXorO(diagonalState[FORWARD]) && (diagonalState[FORWARD] == diagonalState[BACKWARD]));
}

bool TicTacToe::isXorO(char character){
    return character == 'x' || character == 'o';
}

bool TicTacToe::isEmptyBoard(char** board) {

    for(int row = 0; row < SIZE; row++){
        for(int col = 0; col < SIZE; col++){
            if(isXorO(board[row][col])){
                return false;
            }
        }
    }
    return true;
}

int TicTacToe::getXCount() {
    return XCount;
}

int TicTacToe::getOCount() {
    return OCount;
}




