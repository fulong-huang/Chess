#include "chessBoardTest.h"

void testChessBoard(){
    basicMovement();
    validateMovement();
}

void basicMovement(){
    Test boardTest("Testing chess board functions");
    ChessBoard board1, board2;
    boardTest.compare(
            board1.getBoard(), board2.getBoard(),
            "Compare two initialized board"
            );

    boardTest.compare(
            board1.move({0, 1}, {2, 2}), false,
            "Move on WRONG turn (first try) "
            );
    boardTest.compare(
            board1.move({0, 1}, {2, 2}), false,
            "Move on WRONG turn (second try) "
            );

    boardTest.compare(
            board1.move({7, 1}, {5, 2}), true,
            "Move on correct turn"
            );
    boardTest.compare(
            board1.move({5, 2}, {7, 1}), false,
            "Moving same color twice"
            );

    boardTest.compare(
            board1.compare(board2), false,
            "Check if board differs after move"
            );

    boardTest.compare(
            board1.move({0, 1}, {2, 2}), true,
            "Black move"
            );
    boardTest.compare(
            board1.move({5, 2}, {7, 1}), true,
            "White move back"
            );
    boardTest.compare(
            board1.move({2, 2}, {0, 1}), true,
            "Black move back"
            );

    boardTest.compare(
            board1.compare(board2), true,
            "Check if board is same"
            );

    boardTest.compare(
            board1.compare(board2), true,
            "Check if board same after moving Knight back"
            );

    boardTest.compare(
            board1.move({2, 2}, {3, 3}),  false,
            "Move empty piece"
            );


    boardTest.printResult(
            "Test Chess Board Result: "
            );
}


void validateMovement(){
    Test test("Testint constrained movement");
    ChessBoard board, stage;

    // Failed Test might appear as passed
    test.compare(
                board.move({6, 3}, {3, 3}), false,
                "Pawn 1"
            );
    board = stage;
    test.compare(
                board.move({6, 3}, {6, 2}), false,
                "Pawn 2"
            );
    board = stage;
    test.compare(
                board.move({6, 3}, {5, 4}), false,
                "Pawn 3"
            );
    board = stage;
    test.compare(
                board.move({6, 3}, {7, 3}), false,
                "Pawn 4"
            );


    stage.move({6, 3}, {4, 3});
    board = stage;
    test.compare(
                board.move({1, 3}, {0, 3}), false,
                "Pawn 5"
            );
    board = stage;
    test.compare(
                board.move({1, 3}, {4, 3}), false,
                "Pawn 6"
            );
    board = stage;
    test.compare(
                board.move({1, 3}, {1, 2}), false,
                "Pawn 7"
            );
    board = stage;
    test.compare(
                board.move({1, 3}, {2, 4}), false,
                "Pawn 8"
            );

    test.printResult("Invalid Movement Test Result: ");
}



