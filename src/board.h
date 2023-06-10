#pragma once
#include <iostream>
#include <vector>
class ChessBoard{

public: 
    ChessBoard();
    void printBoard();
    std::vector<char> getBoard();

private:
    std::vector<char> board;
    int turn;
};

