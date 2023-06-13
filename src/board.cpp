#include "board.h"

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

    bool movedPiece = this->movePiece(from, to);
    if(!movedPiece){
        return false;
    }

    this->whiteTurn = !this->whiteTurn;

    return true;
}


bool ChessBoard::inCheck(){
    char kingChar = 'K';
    int kingPos;
    if(this->whiteTurn){
        kingChar = 'k';
    }
    for(int i = 0; i < this->board.size(); i++){
        if(this->board[i] == kingChar){
            kingPos = i;
            break;
        }
    }
    
    for(int i = 0; i < this->board.size(); i++){
        if(this->board[i] == '-'){
            continue;
        }
        bool isOpponent = 
            (
                this->whiteTurn && this->board[i] < 97
            ) || 
            (
                !this->whiteTurn && this->board[i] >= 97
            );
        if(!isOpponent){
            continue;
        }
        switch(std::toupper(this->board[i])){
            case 'A':{
                         if(checkPawnMovement(i, kingPos))
                             return true;
                         break;
                     }
            case 'R':{
                         break;
                     }
            case 'N':{
                         break;
                     }
            case 'B':{
                         break;
                     }
            case 'Q':{
                         break;
                     }
            case 'K':{
                         break;
                     }
        }
    }
    return false;
}

bool ChessBoard::movePiece(
    std::pair<int, int> from, std::pair<int, int> to
){
    bool isValidMove = true;
    if(from.first < 0 || from.second < 0 || 
            to.first < 0 || to.second < 0 ||
            from.first >= 8 || from.second >= 8 ||
            to.first >= 8 || to.second >= 8){
        return false;
    }
    int curr = from.first * 8 + from.second;
    int target = to.first * 8 + to.second;
    if(this->board[curr] == '-'){
        return false;
    }
    bool inPlaceMovement = 
        from.first == to.first && from.second == to.second;
    if(inPlaceMovement){
        // UnSelect?
        return false;
    }
    
    char movingPiece = std::tolower(this->board[curr]);
    switch(movingPiece){
        case 'a':
        {
            isValidMove = checkPawnMovement(from, to);
            if(! isValidMove){
                return false;
            }
            break;
         }
        case 'r':
            isValidMove = checkRookMovement(from, to);
            if(!isValidMove){
                return false;
            }
            break;
        case 'n':
            isValidMove = checkKnightMovement(from, to);
            if(!isValidMove){
                return false;
            }
            break;
        case 'b':
            isValidMove = checkBishopMovement(from, to);
            if(!isValidMove){
                return false;
            }
            break;
        case 'q':
            isValidMove = checkQueenMovement(from, to);
            if(!isValidMove){
                return false;
            }
            break;
        case 'k':
            isValidMove = checkKingMovement(from, to);
            if(!isValidMove){
                return false;
            }
            break;
    }
    this->board[target] = this->board[curr];
    this->board[curr] = '-';
    return isValidMove;
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


bool ChessBoard::checkPawnMovement(
    std::pair<int, int> from, std::pair<int, int> to
){
    int curr = from.first * 8 + from.second;
    int target = to.first * 8 + to.second;

    int rowDiff;
    int colDiff = std::abs(from.second - to.second);

    if(this->whiteTurn){
        if(from.first <= to.first) return false;
        rowDiff = from.first - to.first;
    }
    else{
        if(from.first >= to.first) return false;
        rowDiff = to.first - from.first;
    }
    
    switch(rowDiff){
        case 1: {
            if(colDiff == 1){
                bool enemyTarget = 
                    this->board[target] - 96 > 0 != 
                    this->whiteTurn;
                if(!enemyTarget || this->board[target] == '-'){
                    return false;
                }
            }
            else{
                return false;
            }
            break;
        }
        case 2: {
            if(colDiff != 0) return false;
            if(this->board[target] != '-'){
                return false;
            }
            int middleRow = (from.first + to.first)/2;
            int middleIdx = 8 * middleRow + to.second;
            bool somethingInBetween = this->board[middleIdx] != '-';
            int validStartRow = 1 + 5 * this->whiteTurn;
            if(from.first != validStartRow || somethingInBetween){
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
    
    for(int i = start; i < end; i += increment){
        if(this->board[i] != '-'){
            return false;
        }
    }
    return true;
}

bool ChessBoard::checkQueenMovement(
        std::pair<int, int> from, std::pair<int, int> to
    ){
    int curr = from.first * 8 + from.second;
    int target = to.first * 8 + to.second;

    int rowDiff = from.first - to.first;
    int colDiff = from.second - to.second;

    bool straightMovement = (
                rowDiff == 0 || colDiff == 0
            );
    bool diagonalMovement = (
                std::abs(rowDiff) ==
                std::abs(colDiff)
            );
    if(!straightMovement && !diagonalMovement){
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
    int increment;
    if(straightMovement){
        if(rowDiff == 0){
            increment = 1;
        }
        else{
            increment = 8;
        }

        if(rowDiff > 0 || colDiff > 0){
            start = target + increment;
            end = curr;
        }
        else{
            start = curr + increment;
            end = target;
        }
    }
    else{
        if(rowDiff > 0){
            if(colDiff > 0){
                increment = 9;
            }
            else{
                increment = 7;
            }
            start = target + increment;
            end = curr;
        }
        else{
            if(colDiff > 0){
                increment = 7;
            }
            else{
                increment = 9;
            }
            start = curr + increment;
            end = target;
        }
    }
    for(int i = start; i < end; i += increment){
        if(this->board[i] != '-'){
            return false;
        }
    }
    return true;
}

bool ChessBoard::checkKingMovement(
        std::pair<int, int> from, std::pair<int, int> to
    ){
    int curr = from.first * 8 + from.second;
    int target = to.first * 8 + to.second;

    int rowDiff = std::abs(from.first - to.first);
    int colDiff = std::abs(from.second - to.second);

    if(rowDiff > 1 || colDiff > 1){
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
    return true;
}

bool ChessBoard::checkPawnMovement(int from, int to){
    return this->checkPawnMovement({from / 8, from % 8}, {to / 8, to % 8});
}
bool ChessBoard::checkRookMovement(int from, int to){
    return this->checkRookMovement({from / 8, from % 8}, {to / 8, to % 8});
}
bool ChessBoard::checkKnightMovement(int from, int to){
    return this->checkKnightMovement({from/8, from%8}, {to/8, to%8});
}
bool ChessBoard::checkBishopMovement(int from, int to){
    return this->checkBishopMovement({from/8, from%8}, {to/8, to%8});
}
bool ChessBoard::checkQueenMovement(int from, int to){
    return this->checkQueenMovement({from/8, from%8}, {to/8, to%8});
}
bool ChessBoard::checkKingMovement(int from, int to){
    return this->checkKingMovement({from/8, from%8}, {to/8, to%8});
}

void ChessBoard::setBoard(std::vector<char> newBoard, bool turn){
    this->board = newBoard;
    this->whiteTurn = turn;
}

ChessBoard& ChessBoard::operator=(ChessBoard board){
    this->whiteTurn = board.whiteTurn;
    this->board = board.getBoard();
    return *this;
}

