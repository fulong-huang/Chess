#pragma once
#include <iostream>
#include <vector>
#include <utility>


class ChessBoard{

public: 
    ChessBoard();
    
    bool move(std::pair<int, int> from, std::pair<int, int> to);

    bool compare(ChessBoard board2);

    void printBoard();
    std::vector<char> getBoard();


private:
    std::vector<char> board;
    bool whiteTurn;
};

