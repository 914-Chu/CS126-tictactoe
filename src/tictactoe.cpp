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
        if (hadWinner(board) || !hasBalanceTurn()) {
            return Evaluation::UnreachableState;
        }else if (isEmptyBoard(board) || isTie(board)) {
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

    char** board = new char* [ROW];
    for(int row = 0; row < ROW; row++){
        board[row] = new char [COL];
        for(int col = 0; col < COL; col++){
            board[row][col]  = str[COL*row + col];
        }
    }
    return board;
}

bool TicTacToe::isFull() {
    return XCount + OCount == BOARD_CAPACITY;
}

bool TicTacToe::hasBalanceTurn() {
    return abs(XCount - OCount) < 2;
}

bool TicTacToe::hadWinner(char** board) {

}

int TicTacToe::getXCount() {
    return XCount;
}

int TicTacToe::getOCount() {
    return OCount;
}




