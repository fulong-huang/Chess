#include "chessBoardTest.h"

void testChessBoard(){
    Test boardTest("Testing chess board functions");
    ChessBoard board1, board2;
    boardTest.compare(board1.getBoard(), board2.getBoard(),
            "Compare two initialized board"
    );

    boardTest.printResult(
            "Test Chess Board Result: "
    );
}

