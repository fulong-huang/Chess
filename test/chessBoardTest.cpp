#include "chessBoardTest.h"

void testChessBoard(){
    basicMovement();
    testBasicPawnMovement();
    testBasicRookMovement();
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

void testBasicPawnMovement(){
    Test test("Testing basic pawn movement");
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

void testBasicRookMovement(){
    Test test("Testing Basic Rook Movement");
    ChessBoard board, stage;

    test.compare(
            board.move({7, 0}, {7, 2}),
            false,
            "taking own piece"
            );
    
    board = stage;
    test.compare(
            board.move({7, 0}, {5, 0}),
            false,
            "Jump Over Pawn"
            );
    
    // setup
    stage.move({6, 0}, {4, 0});
    stage.move({1, 7}, {3, 7});

    test.compare(stage.getBoard(),
            {
                'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R',  // 0 Black
                'A', 'A', 'A', 'A', 'A', 'A', 'A', '-',  // 1
                '-', '-', '-', '-', '-', '-', '-', '-',  // 2
                '-', '-', '-', '-', '-', '-', '-', 'A',  // 3
                'a', '-', '-', '-', '-', '-', '-', '-',  // 4
                '-', '-', '-', '-', '-', '-', '-', '-',  // 5
                '-', 'a', 'a', 'a', 'a', 'a', 'a', 'a',  // 6
                'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r',  // 7 White
            },
            "Check curent board stage"
        );

    board = stage;
    test.compare(
                board.move({7, 0}, {4, 0}),
                false,
                "Taking own pawn"
            );
    board = stage;
    test.compare(
                board.move({7, 0}, {2, 0}),
                false,
                "Skip over own pawn"
            );
    test.compare(stage.getBoard(),
            {
                'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R',  // 0 Black
                'A', 'A', 'A', 'A', 'A', 'A', 'A', '-',  // 1
                '-', '-', '-', '-', '-', '-', '-', '-',  // 2
                '-', '-', '-', '-', '-', '-', '-', 'A',  // 3
                'a', '-', '-', '-', '-', '-', '-', '-',  // 4
                '-', '-', '-', '-', '-', '-', '-', '-',  // 5
                '-', 'a', 'a', 'a', 'a', 'a', 'a', 'a',  // 6
                'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r',  // 7 White
            },
            "Check curent board stage"
        );


    test.compare(
                stage.move({7, 0}, {5, 0}),
                true,
                "Move (W) Rook Up"
            );
    test.compare(
                stage.move({0, 7}, {1, 7}),
                true,
                "Move (B) Rook Down"
            );
    test.compare(
                stage.move({5, 0}, {5, 4}),
                true,
                "Move (W) Rook to middle"
            );
    test.compare(
                stage.move({1, 0}, {3, 0}),
                true,
                "Move (B) Pawn Down"
            );
    test.compare(
                stage.move({5, 4}, {1, 4}),
                true,
                "Take (B) Pawn"
            );
    test.compare(
                stage.move({1, 6}, {3, 6}),
                true,
                "Move (B) Pawn Down"
            );
    board = stage;
    test.compare(
                board.move({1, 4}, {1, 0}),
                false,
                "Skip over Enemy pieces"
            );
    board = stage;
    test.compare(
                board.move({1, 4}, {1, 2}),
                false,
                "Take (B) Piece by Skip over Enemy pieces"
            );
    board = stage;
    test.compare(
                board.move({1, 4}, {1, 3}),
                true,
                "Take (B) Rook Hozontally"
            );
    test.compare(
                board.move({1, 7}, {1, 2}),
                false,
                "Take (B) own piece"
            );
}


