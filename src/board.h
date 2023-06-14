#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <stdlib.h>


class ChessBoard{

    const char pieceName[7] = {
        '-', 'A', 'R', 'N', 'B', 'Q', 'K',
    };
    
    enum Pieces{
        EMPTY = 0,
        PAWN = 1,
        ROOK = 2,
        KNIGHT = 3,
        BISHOP = 4,
        QUEEN = 5, 
        KING = 6,
    };

public: 
    ChessBoard();
    
    bool move(std::pair<int, int> from, std::pair<int, int> to);

    bool boardInCheck();
    bool gameIsRunning();
    bool compare(ChessBoard board2);

    void printBoard();
    std::vector<char> getBoard();

    ChessBoard& operator=(ChessBoard board);
    void setBoard(std::vector<char> target, bool turn = true);
    

private:
    std::vector<char> board;
    bool whiteTurn;
    bool gameRunning;
    int whiteKingPos, blackKingPos;
    std::map<int, std::vector<int>> validMovements;
    int whitePassant, blackPassant;
    int whiteKingSideCastle, whiteQueenSideCastle;
    int blackKingSideCastle, blackQueenSideCastle;

    void switchTurn();
    void findValidMovements();
    bool validateMove(int from, int to);

    bool checkPawnMovement(std::pair<int, int> from, std::pair<int, int> to);
    bool checkRookMovement(std::pair<int, int> from, std::pair<int, int> to);
    bool checkKnightMovement(std::pair<int, int> from, std::pair<int, int> to);
    bool checkBishopMovement(std::pair<int, int> from, std::pair<int, int> to);
    bool checkQueenMovement(std::pair<int, int> from, std::pair<int, int> to);
    bool checkKingMovement(std::pair<int, int> from, std::pair<int, int> to);

    bool checkPawnMovement(int from, std::pair<int, int> to);
    bool checkRookMovement(int from, std::pair<int, int> to);
    bool checkKnightMovement(int from, std::pair<int, int> to);
    bool checkBishopMovement(int from, std::pair<int, int> to);
    bool checkQueenMovement(int from, std::pair<int, int> to);
    bool checkKingMovement(int from, std::pair<int, int> to);

    bool checkPawnMovement(int from, int to);
    bool checkRookMovement(int from, int to);
    bool checkKnightMovement(int from, int to);
    bool checkBishopMovement(int from, int to);
    bool checkQueenMovement(int from, int to);
    bool checkKingMovement(int from, int to);

    bool pieceAtPosition(int piece, std::pair<int, int> pos);

};

