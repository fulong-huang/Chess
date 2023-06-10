#include "board.h"

ChessBoard::ChessBoard(){
    this->board = {
        'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R',
        'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 
        '-', '-', '-', '-', '-', '-', '-', '-', 
        '-', '-', '-', '-', '-', '-', '-', '-', 
        '-', '-', '-', '-', '-', '-', '-', '-', 
        '-', '-', '-', '-', '-', '-', '-', '-', 
        'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', 
        'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R',
    };
}

void ChessBoard::printBoard(){
    for(int i = 0; i < this->board.size() / 8; i++){
        for(int j = 0; j < 8; j++){
            std::cout << this->board[i * 8 + j] << ' ';
        }
        std::cout << '\n';
    }
}

