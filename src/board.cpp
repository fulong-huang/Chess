#include "board.h"

ChessBoard::ChessBoard(){
    this->board = {
    //   0    1    2    3    4    5    6    7
        'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R',  // 0 Black
        'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',  // 1
        '-', '-', '-', '-', '-', '-', '-', '-',  // 2
        '-', '-', '-', '-', '-', '-', '-', '-',  // 3
        '-', '-', '-', '-', '-', '-', '-', '-',  // 4
        '-', '-', '-', '-', '-', '-', '-', '-',  // 5
        'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',  // 6
        'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r',  // 7 White
    };
    this->whiteTurn = true;
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

    bool correctTurn = this->whiteTurn == (this->board[curr] > 97);
    if(!correctTurn){
        return false;
    }

    bool validMovement = this->validateMovement(from, to);
    if(!validMovement){
        return false;
    }

    this->whiteTurn = !this->whiteTurn;

//    this->board[target] = this->board[curr];
//    this->board[curr] = '-';

    return true;
}

bool ChessBoard::validateMovement(
    std::pair<int, int> from, std::pair<int, int> to
){
    int curr = from.first * 8 + from.second;
    int target = to.first * 8 + to.second;
    if(this->board[curr] == '-'){
        return false;
    }
//    if(this->board[target] != '-'){
//        bool takeOwnPiece = this->whiteTurn == (this->board[target] >= 97);
//        if(takeOwnPiece){
//            return false;
//        }
//    }
    
    char movingPiece = std::tolower(this->board[curr]);
    switch(movingPiece){
        case 'p':
            return checkPawnMovement(from, to);
            break;
        case 'r':
            break;
        case 'n':
            break;
        case 'b':
            break;
        case 'q':
            break;
        case 'k':
            break;
    }

    return true;
}

bool ChessBoard::checkPawnMovement(
    std::pair<int, int> from, std::pair<int, int> to
){
    int curr = from.first * 8 + from.second;
    int target = to.first * 8 + to.second;
    
    int rowDiff = std::abs(from.first - to.first);
    int colDiff = std::abs(from.second - to.second);

    bool isEmptyTarget = this->board[target] == '-';
    if(!isEmptyTarget) return false;

    switch(rowDiff){
        case 1: {
            if(colDiff == 0){
                this->board[target] = this->board[curr];
                this->board[curr] = '-';
            }
            else if(colDiff == 1){
                int facing = 8 * to.first + from.second;
                bool enemyInFront = 
                    this->board[facing] - 97 > 0 != 
                    this->whiteTurn;
                enemyInFront = enemyInFront && 
                    this->board[facing] != '-';
                if(enemyInFront){
                    this->board[facing] = '-';
                    this->board[target] = this->board[curr];
                    this->board[curr] = '-';
                }
                else{
                    return false;
                }
            }
            break;
        }
        case 2: {
            if(colDiff != 0) return false;
            int middleRow = (from.first + to.first)/2;
            int middleIdx = 8 * middleRow + to.second;
            bool nothingInBetween = this->board[middleIdx] == '-';
            int validStartRow = 1 + 5 * this->whiteTurn;
            if(from.first == validStartRow && nothingInBetween){
                this->board[target] = this->board[curr];
                this->board[curr] = '-';
            }
            else{
                return false;
            }
            break;
        }
        default:
            return false;
    }
    
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


ChessBoard& ChessBoard::operator=(ChessBoard board){
    this->whiteTurn = board.whiteTurn;
    this->board = board.getBoard();
    return *this;
}

