#include "board.h"

ChessBoard::ChessBoard(){
    this->whiteTurn = true;
    this->board = {
    //   0    1    2    3    4    5    6    7
        ROOK,   KNIGHT, BISHOP, QUEEN,  KING,   BISHOP, KNIGHT, ROOK,   // 0
        PAWN,   PAWN,   PAWN,   PAWN,   PAWN,   PAWN,   PAWN,   PAWN,   // 1
        EMPTY,  EMPTY,  EMPTY,  EMPTY,  EMPTY,  EMPTY,  EMPTY,  EMPTY,  // 2
        EMPTY,  EMPTY,  EMPTY,  EMPTY,  EMPTY,  EMPTY,  EMPTY,  EMPTY,  // 3
        EMPTY,  EMPTY,  EMPTY,  EMPTY,  EMPTY,  EMPTY,  EMPTY,  EMPTY,  // 4
        EMPTY,  EMPTY,  EMPTY,  EMPTY,  EMPTY,  EMPTY,  EMPTY,  EMPTY,  // 5
        PAWN,   PAWN,   PAWN,   PAWN,   PAWN,   PAWN,   PAWN,   PAWN,   // 6
        ROOK,   KNIGHT, BISHOP, QUEEN,  KING,   BISHOP, KNIGHT, ROOK,   // 7
    };
    for(int i = 48; i < this->board.size(); i++){
        this->board[i] += 10;
    }
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

    bool movingEnemyPiece = this->whiteTurn == (this->board[curr] < 10);
    if(movingEnemyPiece){
        return false;
    }

    bool movedPiece = this->movePiece(from, to);
    if(!movedPiece){
        return false;
    }

    this->whiteTurn = !this->whiteTurn;

    return true;
}


bool ChessBoard::boardInCheck(){
    char kingChar = KING;
    int kingPos;
    if(this->whiteTurn){
        kingChar += 10;
    }
    for(int i = 0; i < this->board.size(); i++){
        if(this->board[i] == kingChar){
            kingPos = i;
            break;
        }
    }

    this->whiteTurn = !this->whiteTurn;
    for(int i = 0; i < this->board.size(); i++){
        if(this->board[i] == 0){
            continue;
        }
        bool isOpponent = this->whiteTurn != this->board[i] < 10;
        if(!isOpponent){
            continue;
        }
        switch(this->board[i] % 10){
            case PAWN:{
                         if(this->checkPawnMovement(i, kingPos)){
                             this->whiteTurn = !this->whiteTurn;
                             return true;
                         }
                         break;
                     }
            case ROOK:{
                         if(this->checkRookMovement(i, kingPos)){
                             this->whiteTurn = !this->whiteTurn;
                             return true;
                         }
                         break;
                     }
            case KNIGHT:{
                         if(this->checkKnightMovement(i, kingPos)){
                             this->whiteTurn = !this->whiteTurn;
                             return true;
                         }
                         break;
                     }
            case BISHOP:{
                         if(this->checkBishopMovement(i, kingPos)){
                             this->whiteTurn = !this->whiteTurn;
                             return true;
                         }
                         break;
                     }
            case QUEEN:{
                         if(this->checkQueenMovement(i, kingPos)){
                             this->whiteTurn = !this->whiteTurn;
                             return true;
                         }
                         break;
                     }
//            case KING:{
//                         break;
//                     }
        }
    }
    this->whiteTurn = !this->whiteTurn;
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
    if(this->board[curr] == 0){
        return false;
    }
    bool inPlaceMovement = 
        from.first == to.first && from.second == to.second;
    if(inPlaceMovement){
        // UnSelect?
        return false;
    }
    
    int movingPiece = this->board[curr] % 10;
    switch(movingPiece){
        case PAWN:
        {
            isValidMove = checkPawnMovement(from, to);
            if(! isValidMove){
                return false;
            }
            break;
         }
        case ROOK:
            isValidMove = checkRookMovement(from, to);
            if(!isValidMove){
                return false;
            }
            break;
        case KNIGHT:
            isValidMove = checkKnightMovement(from, to);
            if(!isValidMove){
                return false;
            }
            break;
        case BISHOP:
            isValidMove = checkBishopMovement(from, to);
            if(!isValidMove){
                return false;
            }
            break;
        case QUEEN:
            isValidMove = checkQueenMovement(from, to);
            if(!isValidMove){
                return false;
            }
            break;
        case KING:
            isValidMove = checkKingMovement(from, to);
            if(!isValidMove){
                return false;
            }
            break;
    }
    this->board[target] = this->board[curr];
    this->board[curr] = 0;
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
    std::string board = "";
    for(int i = 0; i < this->board.size(); i += 8){
        for(int j = 0; j < 8; j++){
            char curr;
            if(this->board[i + j] > 10){
                curr = pieceName[this->board[i + j] - 10];
                curr = tolower(curr);
            }
            else{
                curr = pieceName[this->board[i + j]];
            }
            board += curr;
            board += ", ";
        }
        board += '\n';
    }
    std::cout << board << std::endl;
}

std::vector<char> ChessBoard::getBoard(){
    std::vector<char> copy;
    for(int i = 0; i < this->board.size(); i++){
        if(this->board[i] < 10){
            copy.push_back(pieceName[this->board[i]]);
        }
        else{
            copy.push_back(tolower(pieceName[this->board[i] - 10]));
        }
    }
    return copy;
}


bool ChessBoard::checkPawnMovement(
    std::pair<int, int> from, std::pair<int, int> to
){
    int curr = from.first * 8 + from.second;
    int target = to.first * 8 + to.second;

    int rowDiff;
    int colDiff = std::abs(from.second - to.second);

    if(this->whiteTurn){
        bool movingBackward = from.first <= to.first;
        if(movingBackward) return false;
        rowDiff = from.first - to.first;
    }
    else{
        bool movingBackward = to.first <= from.first;
        if(movingBackward) return false;
        rowDiff = to.first - from.first;
    }
    
    switch(rowDiff){
        case 1: {
            if(colDiff == 1){
                bool enemyTarget = 
                    this->whiteTurn == (this->board[target] < 10);
                if(!enemyTarget || this->board[target] == 0){
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
            if(this->board[target] != 0){
                return false;
            }
            int middleRow = (from.first + to.first)/2;
            int middleIdx = 8 * middleRow + to.second;
            bool somethingInBetween = this->board[middleIdx] != 0;
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
        this->board[target] == 0 ||
        (
            this->whiteTurn == (this->board[target] < 10)
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
            if(this->board[from.first * 8 + i] != 0){
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
            if(this->board[i * 8 + from.second] != 0){
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
        this->board[target] == 0 ||
        (
            this->whiteTurn == (this->board[target] < 10)
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
        this->board[target] == 0 ||
        (
            this->whiteTurn == (this->board[target] < 10)
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
        if(this->board[i] != 0){
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
        this->board[target] == 0 ||
        (
            this->whiteTurn == (this->board[target] < 10)
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
        if(this->board[i] != 0){
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
        this->board[target] == 0 ||
        (
            this->whiteTurn == (this->board[target] < 10)
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
    this->board.clear();
    for(int i = 0; i < newBoard.size(); i++){
        char piece;
        switch(toupper(newBoard[i])){
            case '-':
                piece = 0;
                break;
            case 'A':
                piece = PAWN;
                break;
            case 'R':
                piece = ROOK;
                break;
            case 'N':
                piece = KNIGHT;
                break;
            case 'B':
                piece = BISHOP;
                break;
            case 'Q':
                piece = QUEEN;
                break;
            case 'K':
                piece = KING;
                break;
        }
        if(newBoard[i] > 97){
            piece += 10;
        }
        this->board.push_back(piece);
    }
    this->whiteTurn = turn;
}

ChessBoard& ChessBoard::operator=(ChessBoard board){
    this->whiteTurn = board.whiteTurn;
    this->board = board.board;
    return *this;
}

