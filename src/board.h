#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <stdlib.h>


class ChessBoard{

public: 
    ChessBoard();
    
    bool move(std::pair<int, int> from, std::pair<int, int> to);

    bool compare(ChessBoard board2);

    void printBoard();
    std::vector<char> getBoard();

    ChessBoard& operator=(ChessBoard board);

private:
    std::vector<char> board;
    bool whiteTurn;
    
    bool validateMovement(std::pair<int, int> from, std::pair<int, int> to);
    bool checkPawnMovement(std::pair<int, int> from, std::pair<int, int> to);
};

