#include "testBasicMovement.h"

void testBasicMovements(){
    std::vector<Test> testList;
    testList.push_back(testBasicPawnMovement());
    testList.push_back(testBasicRookMovement());
    testList.push_back(testBasicKnightMovement());
    testList.push_back(testBasicBishopMovement());
    testList.push_back(testBasicQueenMovement());
    testList.push_back(testBasicKingMovement());
    Test::printTestSuit(testList, "Test Basic Movements");
}

Test testBasicPawnMovement(){
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

    return test;
}

Test testBasicKnightMovement(){
    Test test("Testing Basic Knight Movement");
    ChessBoard board, stage;

    test.compare(
            board.move({7, 1}, {5, 3}),
            false,
            "Invalid Movement Diagonal"
            );
    board = stage;
    test.compare(
            board.move({7, 1}, {6, 3}),
            false,
            "Invalid Movement Capture own Piece"
            );

    board = stage;
    test.compare(
            stage.move({7, 1}, {5, 2}),
            true,
            "Move Knight out (W)"
            );
    board = stage;
    test.compare(
            board.move({0, 1}, {2, 3}),
            false,
            "Invalid Diagonal (B)"
            );
    board = stage;
    test.compare(
            board.move({0, 1}, {1, 3}),
            false,
            "Invalid Diagonal Capture Own Pieces (B)"
            );
    board = stage;
    test.compare(
                board.getBoard(),
                {
                'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R',  // 0 Black
                'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A',  // 1
                '-', '-', '-', '-', '-', '-', '-', '-',  // 2
                '-', '-', '-', '-', '-', '-', '-', '-',  // 3
                '-', '-', '-', '-', '-', '-', '-', '-',  // 4
                '-', '-', 'n', '-', '-', '-', '-', '-',  // 5
                'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a',  // 6
                'r', '-', 'b', 'q', 'k', 'b', 'n', 'r',  // 7 White
                },
                "Check state of board"
            );

    test.compare(
            board.move({0, 1}, {2, 2}),
            true,
            "Move Knight out (B)"
            );

    test.compare(
            board.move({5, 2}, {4, 4}),
            true,
            "Move Knight to Center (W)"
            );
    test.compare(
            board.move({2, 2}, {4, 1}),
            true,
            "Move Knight to Center (B)"
            );
    test.compare(
            board.move({4, 4}, {3, 2}),
            true,
            "Push Knight forawrd (W)"
            );
    test.compare(
            board.move({4, 1}, {6, 2}),
            true,
            "Capture Pawn (B) [Check Mate]"
            );
    
    return test;
}

Test testBasicBishopMovement(){
    Test test("Testing Basic Bishop Movement");
    ChessBoard board, stage;

    test.compare(
            board.move({7, 2}, {6, 3}),
            false,
            "Invalid Movement Take Own Piece"
            );
    board = stage;
    test.compare(
            board.move({7, 2}, {5, 4}),
            false,
            "Invalid Movement Skip Over Piece"
            );

    board = stage;
    
    stage.move({6, 4}, {4, 4});
    stage.move({1, 4}, {3, 4});
    stage.move({6, 3}, {4, 3});
    board = stage;
    test.compare(
                board.getBoard(),
                {
            //   0    1    2    3    4    5    6    7
                'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R',  // 0 Black
                'A', 'A', 'A', 'A', '-', 'A', 'A', 'A',  // 1
                '-', '-', '-', '-', '-', '-', '-', '-',  // 2
                '-', '-', '-', '-', 'A', '-', '-', '-',  // 3
                '-', '-', '-', 'a', 'a', '-', '-', '-',  // 4
                '-', '-', '-', '-', '-', '-', '-', '-',  // 5
                'a', 'a', 'a', '-', '-', 'a', 'a', 'a',  // 6
                'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r',  // 7 White
                },
                "Check state of board (Pawns out)"
            );

    board = stage;
    test.compare(
            board.move({0, 5}, {2, 7}),
            false,
            "Invalid Diagonal (B)"
            );
    board = stage;
    test.compare(
            board.move({0, 5}, {1, 6}),
            false,
            "Invalid Diagonal Capture Own Pieces (B)"
            );
    board = stage;
    test.compare(
                board.getBoard(),
                {
            //   0    1    2    3    4    5    6    7
                'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R',  // 0 Black
                'A', 'A', 'A', 'A', '-', 'A', 'A', 'A',  // 1
                '-', '-', '-', '-', '-', '-', '-', '-',  // 2
                '-', '-', '-', '-', 'A', '-', '-', '-',  // 3
                '-', '-', '-', 'a', 'a', '-', '-', '-',  // 4
                '-', '-', '-', '-', '-', '-', '-', '-',  // 5
                'a', 'a', 'a', '-', '-', 'a', 'a', 'a',  // 6
                'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r',  // 7 White
                },
                "Check state of board"
            );

    test.compare(
            board.move({0, 5}, {5, 0}),
            true,
            "Move Bishop out (B)"
            );

    test.compare(
            board.move({7, 2}, {4, 5}),
            true,
            "Move Bishop to Center (W)"
            );
    test.compare(
            board.move({5, 0}, {6, 1}),
            true,
            "Capture White Piece (B)"
            );
    test.compare(
            board.move({4, 5}, {3, 4}),
            true,
            "Capture Black Piece (W)"
            );
    test.compare(
            board.move({6, 1}, {7, 2}),
            true,
            "Capture white piece (B)"
            );
    test.compare(
                board.getBoard(),
                {
            //   0    1    2    3    4    5    6    7
                'R', 'N', 'B', 'Q', 'K', '-', 'N', 'R',  // 0 Black
                'A', 'A', 'A', 'A', '-', 'A', 'A', 'A',  // 1
                '-', '-', '-', '-', '-', '-', '-', '-',  // 2
                '-', '-', '-', '-', 'b', '-', '-', '-',  // 3
                '-', '-', '-', 'a', 'a', '-', '-', '-',  // 4
                '-', '-', '-', '-', '-', '-', '-', '-',  // 5
                'a', '-', 'a', '-', '-', 'a', 'a', 'a',  // 6
                'r', 'n', 'B', 'q', 'k', 'b', 'n', 'r',  // 7 White
                },
                "Check state of board"
            );
    return test;
}

Test testBasicQueenMovement(){
    Test test("Testing Basic Queen Movement");
    ChessBoard board, stage;
    test.compare(
            board.move({7, 3}, {6, 3}),
            false,
            "Invalid Movement Take Own Piece (Vertical)"
            );
    board = stage;
    test.compare(
            board.move({7, 3}, {5, 3}),
            false,
            "Invalid Movement Skip Over Piece (Vertical)"
            );

    test.compare(
            board.move({7, 3}, {7, 4}),
            false,
            "Invalid Movement Take Own Piece (Diagonal)"
            );
    board = stage;
    test.compare(
            board.move({7, 3}, {5, 1}),
            false,
            "Invalid Movement Skip Over Piece (Diagonal)"
            );

    board = stage;
    
    stage.move({6, 3}, {4, 3});
    stage.move({1, 4}, {3, 4});
    stage.move({7, 3}, {5, 3});
    board = stage;
    test.compare(
                board.getBoard(),
                {
            //   0    1    2    3    4    5    6    7
                'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R',  // 0 Black
                'A', 'A', 'A', 'A', '-', 'A', 'A', 'A',  // 1
                '-', '-', '-', '-', '-', '-', '-', '-',  // 2
                '-', '-', '-', '-', 'A', '-', '-', '-',  // 3
                '-', '-', '-', 'a', '-', '-', '-', '-',  // 4
                '-', '-', '-', 'q', '-', '-', '-', '-',  // 5
                'a', 'a', 'a', '-', 'a', 'a', 'a', 'a',  // 6
                'r', 'n', 'b', '-', 'k', 'b', 'n', 'r',  // 7 White
                },
                "Check state of board (Pawns out)"
            );

    board = stage;
    test.compare(
            board.move({0, 3}, {2, 1}),
            false,
            "Invalid Diagonal (B)"
            );
    board = stage;
    test.compare(
            board.move({0, 3}, {1, 2}),
            false,
            "Invalid Diagonal Capture Own Pieces (B)"
            );
    board = stage;
    test.compare(
                board.getBoard(),
                {
            //   0    1    2    3    4    5    6    7
                'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R',  // 0 Black
                'A', 'A', 'A', 'A', '-', 'A', 'A', 'A',  // 1
                '-', '-', '-', '-', '-', '-', '-', '-',  // 2
                '-', '-', '-', '-', 'A', '-', '-', '-',  // 3
                '-', '-', '-', 'a', '-', '-', '-', '-',  // 4
                '-', '-', '-', 'q', '-', '-', '-', '-',  // 5
                'a', 'a', 'a', '-', 'a', 'a', 'a', 'a',  // 6
                'r', 'n', 'b', '-', 'k', 'b', 'n', 'r',  // 7 White
                },
                "Check state of board"
            );

    test.compare(
            board.move({0, 3}, {4, 7}),
            true,
            "Move Queen out (B)"
            );

    test.compare(
            board.move({5, 3}, {1, 7}),
            true,
            "Capture Pawn (W)"
            );
    test.compare(
            board.move({4, 7}, {6, 7}),
            true,
            "Capture White Piece (B)"
            );
    test.compare(
            board.move({1, 7}, {0, 7}),
            true,
            "Capture Black Piece (W)"
            );
    test.compare(
            board.move({6, 7}, {6, 6}),
            true,
            "Capture white piece (B)"
            );
    test.compare(
                board.getBoard(),
                {
            //   0    1    2    3    4    5    6    7
                'R', 'N', 'B', '-', 'K', 'B', 'N', 'q',  // 0 Black
                'A', 'A', 'A', 'A', '-', 'A', 'A', '-',  // 1
                '-', '-', '-', '-', '-', '-', '-', '-',  // 2
                '-', '-', '-', '-', 'A', '-', '-', '-',  // 3
                '-', '-', '-', 'a', '-', '-', '-', '-',  // 4
                '-', '-', '-', '-', '-', '-', '-', '-',  // 5
                'a', 'a', 'a', '-', 'a', 'a', 'Q', '-',  // 6
                'r', 'n', 'b', '-', 'k', 'b', 'n', 'r',  // 7 White
                },
                "Check state of board"
            );
    return test;
}

Test testBasicKingMovement(){
    Test test("Testing Basic King Movement");
    ChessBoard board, stage;
    test.compare(
            board.move({7, 4}, {6, 3}),
            false,
            "Invalid Movement Take Own Piece "
            );
    board = stage;
    test.compare(
            board.move({7, 4}, {6, 4}),
            false,
            "Invalid Movement Take Own Piece "
            );
    board = stage;
    test.compare(
            board.move({7, 4}, {7, 3}),
            false,
            "Invalid Movement Take Own Piece "
            );

    board = stage;
    
    stage.move({6, 3}, {4, 3});
    stage.move({1, 4}, {3, 4});
    stage.move({7, 4}, {6, 3});
    board = stage;
    test.compare(
                board.getBoard(),
                {
            //   0    1    2    3    4    5    6    7
                'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R',  // 0 Black
                'A', 'A', 'A', 'A', '-', 'A', 'A', 'A',  // 1
                '-', '-', '-', '-', '-', '-', '-', '-',  // 2
                '-', '-', '-', '-', 'A', '-', '-', '-',  // 3
                '-', '-', '-', 'a', '-', '-', '-', '-',  // 4
                '-', '-', '-', '-', '-', '-', '-', '-',  // 5
                'a', 'a', 'a', 'k', 'a', 'a', 'a', 'a',  // 6
                'r', 'n', 'b', 'q', '-', 'b', 'n', 'r',  // 7 White
                },
                "Check state of board (Pawns out)"
            );

    board = stage;
    test.compare(
            board.move({0, 4}, {1, 3}),
            false,
            "Invalid Diagonal (B)"
            );
    board = stage;
    test.compare(
            board.move({0, 4}, {0, 3}),
            false,
            "Invalid Straight (B)"
            );
    board = stage;
    test.compare(
                board.getBoard(),
                {
            //   0    1    2    3    4    5    6    7
                'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R',  // 0 Black
                'A', 'A', 'A', 'A', '-', 'A', 'A', 'A',  // 1
                '-', '-', '-', '-', '-', '-', '-', '-',  // 2
                '-', '-', '-', '-', 'A', '-', '-', '-',  // 3
                '-', '-', '-', 'a', '-', '-', '-', '-',  // 4
                '-', '-', '-', '-', '-', '-', '-', '-',  // 5
                'a', 'a', 'a', 'k', 'a', 'a', 'a', 'a',  // 6
                'r', 'n', 'b', 'q', '-', 'b', 'n', 'r',  // 7 White
                },
                "Check state of board"
            );

    test.compare(
            board.move({0, 4}, {1, 4}),
            true,
            "Move King out (B)"
            );

    test.compare(
            board.move({6, 3}, {5, 3}),
            true,
            "Push King (W)"
            );
    test.compare(
            board.move({1, 4}, {2, 5}),
            true,
            "Push King (B)"
            );
    test.compare(
                board.getBoard(),
                {
            //   0    1    2    3    4    5    6    7
                'R', 'N', 'B', 'Q', '-', 'B', 'N', 'R',  // 0 Black
                'A', 'A', 'A', 'A', '-', 'A', 'A', 'A',  // 1
                '-', '-', '-', '-', '-', 'K', '-', '-',  // 2
                '-', '-', '-', '-', 'A', '-', '-', '-',  // 3
                '-', '-', '-', 'a', '-', '-', '-', '-',  // 4
                '-', '-', '-', 'k', '-', '-', '-', '-',  // 5
                'a', 'a', 'a', '-', 'a', 'a', 'a', 'a',  // 6
                'r', 'n', 'b', 'q', '-', 'b', 'n', 'r',  // 7 White
                },
                "Check state of board"
            );
    return test;
}

Test testBasicRookMovement(){
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
    test.compare(stage.getBoard(),
            {
                'R', 'N', 'B', 'Q', 'K', 'B', 'N', '-',  // 0 Black
                '-', 'A', 'A', 'A', 'A', 'A', 'A', 'R',  // 1
                '-', '-', '-', '-', '-', '-', '-', '-',  // 2
                'A', '-', '-', '-', '-', '-', '-', 'A',  // 3
                'a', '-', '-', '-', '-', '-', '-', '-',  // 4
                '-', '-', '-', '-', 'r', '-', '-', '-',  // 5
                '-', 'a', 'a', 'a', 'a', 'a', 'a', 'a',  // 6
                '-', 'n', 'b', 'q', 'k', 'b', 'n', 'r',  // 7 White
            },
            "Check curent board stage"
        );

    test.compare(
                stage.move({5, 4}, {1, 4}),
                true,
                "Take (B) Pawn"
            );
    test.compare(
                stage.move({0, 4}, {1, 4}),
                true,
                "Take (W) ROOK with KING [Escape Check]"
            );
    test.compare(stage.getBoard(),
            {
                'R', 'N', 'B', 'Q', '-', 'B', 'N', '-',  // 0 Black
                '-', 'A', 'A', 'A', 'K', 'A', 'A', 'R',  // 1
                '-', '-', '-', '-', '-', '-', '-', '-',  // 2
                'A', '-', '-', '-', '-', '-', '-', 'A',  // 3
                'a', '-', '-', '-', '-', '-', '-', '-',  // 4
                '-', '-', '-', '-', '-', '-', '-', '-',  // 5
                '-', 'a', 'a', 'a', 'a', 'a', 'a', 'a',  // 6
                '-', 'n', 'b', 'q', 'k', 'b', 'n', 'r',  // 7 White
            },
            "Check curent board stage"
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
    return test;
}

