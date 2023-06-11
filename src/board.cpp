#include "board.h"

ChessBoard::ChessBoard(){
    this->board = {
        'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R',
        'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 
        '-', '-', '-', '-', '-', '-', '-', '-', 
        '-', '-', '-', '-', '-', '-', '-', '-', 
        '-', '-', '-', '-', '-', '-', '-', '-', 
        '-', '-', '-', '-', '-', '-', '-', '-', 
        'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', 
        'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r',
    };
}

bool ChessBoard::move(std::pair<int, int> from, std::pair<int, int> to){
    int curr = from.first * 8 + from.second;
    int target = to.first * 8 + to.second;

    if(curr < 0 || curr >= this->board.size()){
        return false;
    }
    if(target < 0 || target >= this->board.size()){ 
        return false;
    }
    if(this->board[curr] == '-'){
        return false;
    }


    this->board[target] = this->board[curr];
    this->board[curr] = '-';

    return true;
}



bool ChessBoard::compare(ChessBoard board2){
    std::vector<char> secondBoard = board2.getBoard();
    for(int i = 0; i < secondBoard.size(); i++){
        if(this->board[i] != secondBoard[i]){
            return false;
        }
    }
    return true;
}

void ChessBoard::printBoard(){
    for(int i = 0; i < this->board.size() / 8; i++){
        for(int j = 0; j < 8; j++){
            std::cout << this->board[i * 8 + j] << ' ';
        }
        std::cout << '\n';
    }
}

std::vector<char> ChessBoard::getBoard(){
    return this->board;
}

