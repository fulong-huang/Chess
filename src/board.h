#include <iostream>
#include <vector>
class ChessBoard{

public: 
    ChessBoard();
    void printBoard();

private:
    std::vector<char> board;
    int turn;
};

