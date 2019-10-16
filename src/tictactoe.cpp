#include "tictactoe.hpp"
#include<algorithm>
#include<cmath>
#include<vector>

using namespace std;

//Evaluate passed board state with following order:
//Invalid input: if the passed board state string is empty or has unexpected length.
//Unreachable state: if there's more than one winner and isn't a valid edge case or X and O's turn is unbalanced
//No winner: if the board is empty or it's a tie
//X wins: if X wins
//O wins: if O wins
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

//Trim unnecessary spaces in front or after the string
//return a processed string
string TicTacToe::Trim(const string &str) {
    if (str.empty()) {
        return str;
    }
    string unTrim = str;
    unTrim.erase(0,unTrim.find_first_not_of(' '));
    unTrim.erase(unTrim.find_last_not_of(' ') + 1);
    return unTrim;
}

//Turn the board state string into a 2d vector
//return a 2d vector
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

//Check if X and O have balance turns by board state string
//One should not have more than two turns than the other
//return if X and O have balance turns
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

//check if rows have any winner
//return a vector of row's state
vector<char> TicTacToe::CheckRow(vector<vector<char>>board){
    vector<char> state(kSideLength);
    for(unsigned int row = 0; row < kSideLength; row++){
        bool equal = true;
        if(IsXorO(board[row][kFirst])) { //check if the first element is x or o
            for (unsigned int col = 0; col < kSideLength - 1; col++) {
                if (board[row][col] != board[row][col + 1]) {//check if elements in same row are same
                    equal = false;
                    break;
                }
            }
            if (equal) {
                winner_ = board[row][kFirst];//store the results if there's a winner in this row
                state[row] = winner_;
                win_count_++;
            }
        }
    }
    return state;
}

//check if cols have any winner
//return a vector of col's state
vector<char> TicTacToe::CheckCol(vector<vector<char>> board){
    vector<char> state(kSideLength);
    for(unsigned int col = 0; col < kSideLength; col++){
        bool equal = true;
        if(IsXorO(board[kFirst][col])) {//check if the first element is x or o
            for (unsigned int row = 0; row < kSideLength - 1; row++) {
                if (board[row][col] != board[row + 1][col]) {//check if elements in same col are same
                    equal = false;
                    break;
                }
            }
            if (equal) {
                winner_ = board[kFirst][col];//store the results if there's a winner in this col
                state[col] = winner_;
                win_count_++;
            }
        }
    }
    return state;
}

//check if diagonals have any winner
//return a vector of diagonal's state
vector<char> TicTacToe::CheckDiagonal(vector<vector<char>> board){
    vector<char> state(kSideLength);
    bool equal = true;
    if(IsXorO(board[kFirst][kFirst])) {//check if the first element is x or o
        for (unsigned int row = 0; row < kSideLength - 1; row++) {
            unsigned int col = row;
            if (board[row][col] != board[row + 1][col + 1]) {//check if backward diagonal has same elements
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
    if(IsXorO(board[kFirst][kLast])) {//check if the first element is x or o
        for (unsigned int row = 0; row < kSideLength - 1; row++) {
            unsigned int col = kLast - row;
            if (board[row][col] != board[row + 1][col - 1]) {//check if forward diagonal has same elements
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

//check for edge cases
//Any case that has two line other than
// O _ X    O X _    O O O    O O O
// O _ X or O X _ or X X X or _ _ _
// O _ X    O X _    _ _ _    X X X
//can be considered valid since the one that complete the lines could be the last entry.
bool TicTacToe::HasInvalidTwoLine(vector<char> rowState, vector<char> colState, vector<char> diagonalState) {

    return (HasWinner(rowState) != HasWinner(colState)) && !HasWinner(diagonalState);
}

//check if rows or cols or diagonals has winner
bool TicTacToe::HasWinner(vector<char> state) {
    for(char character : state){
        if(IsXorO(character)){
            return true;
        }
    }
    return false;
}

//check if the passed character is X or O
bool TicTacToe::IsXorO(char character){
    return character == 'x' || character == 'o';
}

//check if the board is empty (with any character other than x or o)
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




