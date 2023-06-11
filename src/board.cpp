#include "board.h"
#include <exception>

ChessBoard::ChessBoard(){
    this->whiteTurn = true;
    this->board = {
    //   0    1    2    3    4    5    6    7
        'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R',  // 0 Black
        'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A',  // 1
        '-', '-', '-', '-', '-', '-', '-', '-',  // 2
        '-', '-', '-', '-', '-', '-', '-', '-',  // 3
        '-', '-', '-', '-', '-', '-', '-', '-',  // 4
        '-', '-', '-', '-', '-', '-', '-', '-',  // 5
        'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a',  // 6
        'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r',  // 7 White
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

    bool correctTurn = this->whiteTurn == (this->board[curr] >= 97);
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
    bool inPlaceMovement = 
        from.first == to.first && from.second == to.second;
    if(inPlaceMovement){
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
        case 'a':
            return checkPawnMovement(from, to);
            break;
        case 'r':
            return checkRookMovement(from, to);
            break;
        case 'n':
            return checkKnightMovement(from, to);
            break;
        case 'b':
            return checkBishopMovement(from, to);
            break;
        case 'q':
            return checkQueenMovement(from, to);
            break;
        case 'k':
            return checkKingMovement(from, to);
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
                    this->board[facing] - 96 > 0 != 
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

bool ChessBoard::checkRookMovement(
        std::pair<int, int> from, std::pair<int, int> to
    ){
    int curr = from.first * 8 + from.second;
    int target = to.first * 8 + to.second;

    bool isStraightLine = from.first == to.first || from.second == to.second;
    if(!isStraightLine){
        return false;
    }
    bool validTarget = 
        this->board[target] == '-' ||
        (
            this->board[target] - 96 > 0 != 
            this->whiteTurn
        );
    if(!validTarget){
        return false;
    }
    int start, end;
    if(from.first == to.first){
        if(from.second > to.second){
            start = to.second;
            end = from.second;
        }
        else{
            start = from.second;
            end = to.second;
        }
        for(int i = start + 1; i < end; i++){
            if(this->board[from.first * 8 + i] != '-'){
                return false;
            }
        }
    }
    else{
        if(from.first > to.first){
            start = to.first;
            end = from.first;
        }
        else{
            start = from.first;
            end = to.first;
        }
        for(int i = start + 1; i < end; i++){
            if(this->board[i * 8 + from.second] != '-'){
                return false;
            }
        }
    }
    
    this->board[target] = this->board[curr];
    this->board[curr] = '-';

    return true;
}
bool ChessBoard::checkKnightMovement(
        std::pair<int, int> from, std::pair<int, int> to
    ){
    int curr = from.first * 8 + from.second;
    int target = to.first * 8 + to.second;
    bool validTarget = 
        this->board[target] == '-' ||
        (
            this->board[target] - 96 > 0 != 
            this->whiteTurn
        );
    if(!validTarget){
        return false;
    }
    int rowDiff = std::abs(from.first - to.first);
    int colDiff = std::abs(from.second - to.second);
//    if(std::abs(rowDiff - colDiff) != 1){
//        return false;
//    }
    if(rowDiff != 1 && colDiff != 1 ||
            rowDiff != 2 && colDiff != 2){
        return false;
    }
    
    this->board[target] = this->board[curr];
    this->board[curr] = '-';

    return true;
}
bool ChessBoard::checkBishopMovement(
        std::pair<int, int> from, std::pair<int, int> to
    ){
    int curr = from.first * 8 + from.second;
    int target = to.first * 8 + to.second;
    bool validTarget = 
        this->board[target] == '-' ||
        (
            this->board[target] - 96 > 0 != 
            this->whiteTurn
        );
    if(!validTarget){
        return false;
    }
    int rowDiff = from.first - to.first;
    int colDiff = from.second - to.second;
    bool diagnalMovement = std::abs(rowDiff) == std::abs(colDiff);
    if(!diagnalMovement){
        return false;
    }
    
    int start, end;
    int increment;
    if(rowDiff < 0){
        if(colDiff < 0){
            increment = 9;
        }
        else{
            increment = 7;
        }
        start = curr + increment;
        end = target;
    }
    else{
        if(colDiff < 0){
            increment = 7;
        }
        else{
            increment = 9;
        }
        start = target + increment;
        end = curr;
    }
    
    for(int i = start; i != end; i += increment){
        if(this->board[i] != '-'){
            return false;
        }
    }

    this->board[target] = this->board[curr];
    this->board[curr] = '-';
    
    return true;
}
bool ChessBoard::checkQueenMovement(
        std::pair<int, int> from, std::pair<int, int> to
    ){
    int curr = from.first * 8 + from.second;
    int target = to.first * 8 + to.second;
    return true;
}
bool ChessBoard::checkKingMovement(
        std::pair<int, int> from, std::pair<int, int> to
    ){
    int curr = from.first * 8 + from.second;
    int target = to.first * 8 + to.second;
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

