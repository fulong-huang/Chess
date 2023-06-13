#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <stdlib.h>


class ChessBoard{

public: 
    ChessBoard();
    
    bool move(std::pair<int, int> from, std::pair<int, int> to);

    bool inCheck();
    bool compare(ChessBoard board2);

    void printBoard();
    std::vector<char> getBoard();

    ChessBoard& operator=(ChessBoard board);
    void setBoard(std::vector<char> target, bool turn = true);

private:
    std::vector<char> board;
    bool whiteTurn;
    
    bool movePiece(std::pair<int, int> from, std::pair<int, int> to);
    bool checkPawnMovement(std::pair<int, int> from, std::pair<int, int> to);
    bool checkRookMovement(std::pair<int, int> from, std::pair<int, int> to);
    bool checkKnightMovement(std::pair<int, int> from, std::pair<int, int> to);
    bool checkBishopMovement(std::pair<int, int> from, std::pair<int, int> to);
    bool checkQueenMovement(std::pair<int, int> from, std::pair<int, int> to);
    bool checkKingMovement(std::pair<int, int> from, std::pair<int, int> to);

    bool checkPawnMovement(int from, int to);
    bool checkRookMovement(int from, int to);
    bool checkKnightMovement(int from, int to);
    bool checkBishopMovement(int from, int to);
    bool checkQueenMovement(int from, int to);
    bool checkKingMovement(int from, int to);
};

