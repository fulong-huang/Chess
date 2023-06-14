#include "testSpecialMoves.h"

void testSpecialMoves(){
    std::vector<Test> testLists;
    testLists.push_back(testEnPassant());
    testLists.push_back(testCastle());
    Test::printTestSuit(testLists);
}

Test testEnPassant(){
    Test test("Test En Passant");
    ChessBoard board;
    board.setBoard({
    //   0    1    2    3    4    5    6    7
        '-', '-', '-', '-', 'K', '-', '-', '-',  // 0
        '-', '-', 'A', '-', '-', '-', '-', '-',  // 1
        '-', '-', '-', '-', '-', '-', '-', '-',  // 2
        '-', '-', '-', 'a', '-', '-', '-', '-',  // 3
        '-', '-', '-', '-', '-', '-', '-', '-',  // 4
        '-', '-', '-', '-', '-', '-', '-', '-',  // 5
        '-', '-', '-', '-', '-', '-', '-', '-',  // 6
        '-', '-', '-', '-', 'k', '-', '-', '-',  // 7
            }, false);
    test.compare(board.move({1, 2}, {3, 2}), true,
            "Pawn Move Two Space");
    test.compare(board.move({3, 3}, {2, 2}), true,
                "Capture En Passant");

    board.setBoard({
    //   0    1    2    3    4    5    6    7
        '-', '-', '-', '-', 'K', '-', '-', '-',  // 0
        '-', '-', 'A', '-', '-', '-', '-', '-',  // 1
        '-', '-', '-', '-', '-', '-', '-', '-',  // 2
        '-', '-', '-', 'a', 'a', '-', '-', '-',  // 3
        '-', '-', '-', '-', '-', '-', '-', '-',  // 4
        '-', '-', '-', '-', '-', '-', '-', '-',  // 5
        '-', '-', '-', '-', '-', '-', '-', '-',  // 6
        '-', '-', '-', '-', 'k', '-', '-', '-',  // 7
            }, false);
    test.compare(board.move({1, 2}, {2, 2}), true,
            "Push Pawn Forward (B)");
    test.compare(board.move({3, 4}, {2, 4}), true,
                "Push Pawn Forward (W)");
    test.compare(board.move({2, 2}, {3, 2}), true,
            "Push Pawn Foward Again (B)");
    test.compare(board.move({3, 3}, {2, 2}), false,
            "Attempt En Passant After Slow Push");

    board.setBoard({
    //   0    1    2    3    4    5    6    7
        '-', '-', '-', '-', 'K', '-', '-', '-',  // 0
        '-', '-', 'A', '-', '-', '-', '-', '-',  // 1
        '-', '-', '-', '-', '-', '-', '-', '-',  // 2
        'a', '-', '-', 'a', '-', '-', '-', '-',  // 3
        '-', '-', '-', '-', '-', '-', '-', '-',  // 4
        '-', '-', '-', '-', '-', '-', '-', '-',  // 5
        '-', '-', '-', '-', '-', '-', '-', '-',  // 6
        '-', '-', '-', '-', 'k', '-', '-', '-',  // 7
            }, false);
    test.compare(board.move({1, 2}, {3, 2}), true,
            "Pawn Move Two Space");
    test.compare(board.move({3, 0}, {2, 0}), true,
            "Ignore En Passant Chance");
    test.compare(board.move({0, 4}, {0, 5}), true,
            "Black Move King");
    test.compare(board.move({3, 3}, {2, 2}), false,
            "Attempt En Passant Turn After");

    return test;
}

Test testCastle(){
    Test test("Test Castle");
    ChessBoard board, stage;
    stage.setBoard({
    //   0    1    2    3    4    5    6    7
        'R', '-', '-', '-', 'K', '-', '-', 'R',  // 0
        '-', '-', '-', '-', '-', '-', '-', '-',  // 1
        '-', '-', '-', '-', '-', '-', '-', '-',  // 2
        '-', '-', '-', '-', '-', '-', '-', '-',  // 3
        '-', '-', '-', '-', '-', '-', '-', '-',  // 4
        '-', '-', '-', '-', '-', '-', '-', '-',  // 5
        'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a',  // 6
        'r', '-', '-', '-', 'k', '-', '-', 'r',  // 7
            });
    board = stage;
    test.compare(board.move({7, 4}, {7, 2}), true,
            "White Queen Side Castle");
    test.compare(board.move({0, 4}, {0, 2}), true,
            "Black Queen Side Castle");

    board = stage;
    test.compare(board.move({7, 4}, {7, 6}), true,
            "White King Side Castle");
    test.compare(board.move({0, 4}, {0, 6}), true,
            "Black King Side Castle");

    board = stage;
    board.move({7, 7}, {7, 6});
    board.move({0, 4}, {0, 5});
    board.move({7, 6}, {7, 7});
    board.move({0, 5}, {0, 4});
    
    test.compare(board.move({7, 4}, {7, 6}), false,
            "White King Side Castle After Rook Moved");
    test.compare(board.move({0, 4}, {0, 6}), false,
            "Black King Side Castle After King Moved");


    stage.setBoard({
    //   0    1    2    3    4    5    6    7
        'R', '-', '-', '-', 'K', '-', '-', 'R',  // 0
        '-', '-', '-', '-', '-', '-', '-', '-',  // 1
        '-', '-', '-', '-', '-', '-', '-', '-',  // 2
        '-', '-', '-', '-', '-', '-', '-', '-',  // 3
        '-', '-', '-', '-', '-', '-', '-', '-',  // 4
        '-', '-', '-', '-', '-', '-', '-', '-',  // 5
        '-', '-', '-', '-', 'a', 'a', 'a', 'a',  // 6
        'r', '-', '-', '-', 'k', '-', '-', 'r',  // 7
            });
    board = stage;
    test.compare(board.move({7, 4}, {7, 2}), true,
            "Queen Side Castle When Rook Targeted (Allowed)");
    test.compare(board.move({0, 4}, {0, 2}), false,
            "Attemp Queen Side Castle With Targeted Path");
    test.compare(board.move({0, 4}, {0, 6}), true,
            "Black Castle Other Side");
    
    stage.setBoard({
    //   0    1    2    3    4    5    6    7
        '-', '-', 'R', '-', 'K', '-', '-', 'R',  // 0
        '-', '-', '-', '-', '-', '-', '-', '-',  // 1
        '-', '-', '-', '-', '-', '-', '-', '-',  // 2
        '-', '-', '-', '-', '-', '-', '-', '-',  // 3
        '-', '-', '-', '-', '-', '-', '-', '-',  // 4
        '-', '-', '-', '-', 'r', '-', '-', '-',  // 5
        '-', '-', '-', '-', 'a', 'a', 'a', 'a',  // 6
        'r', '-', '-', '-', 'k', '-', '-', '-',  // 7
            });
    board = stage;
    test.compare(board.move({7, 4}, {7, 2}), false,
            "Castle Into Check");
    board.move({6, 7}, {5, 7});
    test.compare(board.move({0, 4}, {0, 6}), false,
            "Castle From Check");
    board.move({0, 2}, {0, 0});
    test.compare(board.move({7, 4}, {7, 2}), true,
            "Castle After Path Not Targeted");

    return test;
}

