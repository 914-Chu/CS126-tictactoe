#include "tictactoe.hpp"
#include<algorithm>
#include<cmath>

using namespace std;

Evaluation TicTacToe::EvaluateBoard(const string &board_state) {

    string boardState = board_state;
    boardState = trim(boardState);
    transform(boardState.begin(), boardState.end(), boardState.begin(), ::tolower);
    count(boardState);

    if(boardState.empty() || boardState.length() != 9){
        return Evaluation::InvalidInput;
    }else if((!isFull(boardState) && hasTwoWinner(boardState)) || !hasBalanceTurn(boardState)){
        return Evaluation ::UnreachableState;
    }else if(isEmptyBoard(boardState) || isTie(boardState)){
        return Evaluation::NoWinner;
    }else {

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

bool TicTacToe::isFull(const string &str) {
    return XCount + OCount == BOARD_CAPACITY;
}

bool TicTacToe::hasBalanceTurn(const string &str) {
    return abs(XCount - OCount) < 2;
}

bool TicTacToe::hasTwoWinner(const string &str) {


}

int TicTacToe::getXCount() {
    return XCount;
}

int TicTacToe::getOCount() {
    return OCount;
}


