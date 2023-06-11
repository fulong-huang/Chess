#include "chessBoardTest.h"

void testChessBoard(){
    Test boardTest("Testing chess board functions");
    ChessBoard board1, board2;
    boardTest.compare(
        board1.getBoard(), board2.getBoard(),
        "Compare two initialized board"
    );

    boardTest.compare(
        board1.move({0, 1}, {2, 2}), true,
        "Move Knight out"
    );
    
    boardTest.compare(
        board1.compare(board2), false,
        "Check if board differs"
    );

    boardTest.compare(
        board1.move({2, 2}, {0, 1}), true,
        "Move Knight back"
    );
    
    boardTest.compare(
        board1.compare(board2), true,
        "Check if board same after moving Knight back"
    );



    boardTest.printResult(
        "Test Chess Board Result: "
    );
}

