#include "tictactoe.hpp"
#include<algorithm>

using namespace std;

Evaluation TicTacToe::EvaluateBoard(const string &board_state) {

    string boardState = board_state;
    boardState = trim(boardState);
    transform(boardState.begin(), boardState.end(), boardState.begin(), ::tolower);
    int length = boardState.length();
    count(boardState);

    if(boardState.empty() || length != 9){
        return Evaluation::InvalidInput;
    }else if()
}

string& TicTacToe::trim(const string &str)
{
    string unTrim = str;
    if (unTrim.empty())
    {
        return unTrim;
    }

    unTrim.erase(0,unTrim.find_first_not_of(" "));
    unTrim.erase(unTrim.find_last_not_of(" ") + 1);
    return unTrim;
}

void TicTacToe::count(const string &str){


}

int TicTacToe::getXCount(){
    return XCount;
}

int TicTacToe::getOCount(){
    return OCount;
}
