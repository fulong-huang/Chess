#include "testMovementWhileInCheck.h"

void testMovementWhileInCheck(){
    std::vector<Test> testLists;
    testLists.push_back(testIfDetectCheck());
    testLists.push_back(testIfCheckLimitsMovement());
    Test::printTestSuit(testLists);
}

Test testIfDetectCheck(){
    Test test("Test if In Check");
    ChessBoard board;
    test.compare(board.boardInCheck(), false,
            "Not In Check When Game Start");
    board.setBoard({
    //   0    1    2    3    4    5    6    7
        '-', '-', '-', 'K', '-', '-', '-', '-',  // 0
        '-', '-', '-', '-', '-', '-', '-', '-',  // 1
        '-', '-', '-', '-', 'A', '-', '-', '-',  // 2
        '-', '-', '-', '-', '-', 'k', '-', '-',  // 3
        '-', '-', '-', '-', '-', '-', '-', 'a',  // 4
        '-', '-', '-', '-', '-', '-', '-', '-',  // 5
        '-', '-', '-', '-', '-', '-', '-', '-',  // 6
        '-', '-', '-', '-', '-', '-', '-', 'r',  // 7
            });
    test.compare(board.boardInCheck(), true,
            "Detect Checked By Pawn");
    board.setBoard({
    //   0    1    2    3    4    5    6    7
        '-', '-', '-', 'K', '-', '-', '-', '-',  // 0
        '-', '-', '-', '-', '-', '-', '-', '-',  // 1
        '-', '-', '-', '-', '-', '-', '-', '-',  // 2
        '-', '-', 'R', '-', '-', 'k', '-', '-',  // 3
        '-', '-', '-', '-', '-', '-', '-', 'a',  // 4
        '-', '-', '-', '-', '-', '-', '-', '-',  // 5
        '-', '-', '-', '-', '-', '-', '-', '-',  // 6
        '-', '-', '-', '-', '-', '-', '-', 'r',  // 7
            });
    test.compare(board.boardInCheck(), true,
            "Detect Checked By Rook");
    board.setBoard({
    //   0    1    2    3    4    5    6    7
        '-', '-', '-', 'K', '-', '-', '-', '-',  // 0
        '-', '-', '-', '-', '-', '-', '-', '-',  // 1
        '-', '-', '-', '-', '-', '-', '-', '-',  // 2
        '-', '-', '-', '-', '-', 'k', '-', '-',  // 3
        '-', '-', '-', '-', '-', '-', '-', 'a',  // 4
        '-', '-', '-', '-', 'N', '-', '-', '-',  // 5
        '-', '-', '-', '-', '-', '-', '-', '-',  // 6
        '-', '-', '-', '-', '-', '-', '-', 'r',  // 7
            });
    test.compare(board.boardInCheck(), true,
            "Detect Checked By Knight");
    board.setBoard({
    //   0    1    2    3    4    5    6    7
        '-', '-', 'B', 'K', '-', '-', '-', '-',  // 0
        '-', '-', '-', '-', '-', '-', '-', '-',  // 1
        '-', '-', '-', '-', '-', '-', '-', '-',  // 2
        '-', '-', '-', '-', '-', 'k', '-', '-',  // 3
        '-', '-', '-', '-', '-', '-', '-', 'a',  // 4
        '-', '-', '-', '-', '-', '-', '-', '-',  // 5
        '-', '-', '-', '-', '-', '-', '-', '-',  // 6
        '-', '-', '-', '-', '-', '-', '-', 'r',  // 7
            });
    test.compare(board.boardInCheck(), true,
            "Detect Checked By Bishop");
    board.setBoard({
    //   0    1    2    3    4    5    6    7
        '-', '-', '-', 'K', '-', '-', '-', '-',  // 0
        '-', '-', '-', '-', '-', '-', '-', '-',  // 1
        '-', '-', '-', '-', '-', '-', '-', '-',  // 2
        '-', '-', '-', '-', '-', 'k', '-', '-',  // 3
        '-', '-', '-', '-', '-', '-', '-', 'a',  // 4
        '-', '-', '-', '-', '-', '-', '-', '-',  // 5
        '-', '-', 'Q', '-', '-', '-', '-', '-',  // 6
        '-', '-', '-', '-', '-', '-', '-', 'r',  // 7
            });
    test.compare(board.boardInCheck(), true,
            "Detect Checked By Queen");

    std::cout << "\t\tCheck If not false Detection" << std::endl;
    board.setBoard({
    //   0    1    2    3    4    5    6    7
        '-', '-', '-', 'K', '-', '-', '-', '-',  // 0
        '-', '-', '-', '-', '-', '-', '-', '-',  // 1
        '-', '-', '-', '-', '-', '-', '-', '-',  // 2
        '-', '-', '-', '-', 'A', 'k', '-', '-',  // 3
        '-', '-', '-', '-', '-', '-', '-', 'a',  // 4
        '-', '-', '-', '-', '-', '-', '-', '-',  // 5
        '-', '-', '-', '-', '-', '-', '-', '-',  // 6
        '-', '-', '-', '-', '-', '-', '-', 'r',  // 7
            });
    test.compare(board.boardInCheck(), false,
            "Detect if False Checked By Pawn");
    board.setBoard({
    //   0    1    2    3    4    5    6    7
        '-', '-', '-', 'K', '-', '-', '-', '-',  // 0
        '-', '-', '-', '-', '-', '-', '-', '-',  // 1
        '-', '-', '-', '-', '-', '-', '-', '-',  // 2
        '-', '-', 'R', '-', 'a', 'k', '-', '-',  // 3
        '-', '-', '-', '-', '-', '-', '-', 'a',  // 4
        '-', '-', '-', '-', '-', '-', '-', '-',  // 5
        '-', '-', '-', '-', '-', '-', '-', '-',  // 6
        '-', '-', '-', '-', '-', '-', '-', 'r',  // 7
            });
    test.compare(board.boardInCheck(), false,
            "Detect False Checked By Rook");
//    board.setBoard({
//    //   0    1    2    3    4    5    6    7
//        '-', '-', '-', 'K', '-', '-', '-', '-',  // 0
//        '-', '-', '-', '-', '-', '-', '-', '-',  // 1
//        '-', '-', '-', '-', '-', '-', '-', '-',  // 2
//        '-', '-', '-', '-', '-', 'k', '-', '-',  // 3
//        '-', '-', '-', '-', '-', '-', '-', 'a',  // 4
//        '-', '-', '-', '-', 'N', '-', '-', '-',  // 5
//        '-', '-', '-', '-', '-', '-', '-', '-',  // 6
//        '-', '-', '-', '-', '-', '-', '-', 'r',  // 7
//            });
//    test.compare(board.boardInCheck(), true,
//            "Detect Checked By Knight");
    board.setBoard({
    //   0    1    2    3    4    5    6    7
        '-', '-', 'B', 'K', '-', '-', '-', '-',  // 0
        '-', '-', '-', '-', '-', '-', '-', '-',  // 1
        '-', '-', '-', '-', 'a', '-', '-', '-',  // 2
        '-', '-', '-', '-', '-', 'k', '-', '-',  // 3
        '-', '-', '-', '-', '-', '-', '-', 'a',  // 4
        '-', '-', '-', '-', '-', '-', '-', '-',  // 5
        '-', '-', '-', '-', '-', '-', '-', '-',  // 6
        '-', '-', '-', '-', '-', '-', '-', 'r',  // 7
            });
    test.compare(board.boardInCheck(), false,
            "Detect False Checked By Bishop");
    board.setBoard({
    //   0    1    2    3    4    5    6    7
        '-', '-', '-', 'K', '-', '-', '-', '-',  // 0
        '-', '-', '-', '-', '-', '-', '-', '-',  // 1
        '-', '-', '-', '-', '-', '-', '-', '-',  // 2
        '-', '-', '-', '-', '-', 'k', '-', '-',  // 3
        '-', '-', '-', '-', '-', '-', '-', 'a',  // 4
        '-', '-', '-', 'a', '-', '-', '-', '-',  // 5
        '-', '-', 'Q', '-', '-', '-', '-', '-',  // 6
        '-', '-', '-', '-', '-', '-', '-', 'r',  // 7
            });
    test.compare(board.boardInCheck(), false,
            "Detect False Checked By Queen");

    test.printResult();
    return test;
}

Test testIfCheckLimitsMovement(){
    Test test("Test if Movement is Limited When in Check");
    ChessBoard board;

    board.setBoard({
    //   0    1    2    3    4    5    6    7
        '-', '-', '-', 'K', '-', '-', '-', '-',  // 0
        '-', '-', '-', '-', '-', '-', '-', '-',  // 1
        '-', '-', '-', '-', 'A', '-', '-', '-',  // 2
        '-', '-', '-', '-', '-', 'k', '-', '-',  // 3
        '-', '-', '-', '-', '-', '-', '-', 'a',  // 4
        '-', '-', '-', '-', '-', '-', '-', '-',  // 5
        '-', '-', '-', '-', '-', '-', '-', '-',  // 6
        '-', '-', '-', '-', '-', '-', '-', 'r',  // 7
            });
    test.compare(board.move({4, 7}, {3, 7}), false,
            "Not escaping check by Pawn");
    board.setBoard({
    //   0    1    2    3    4    5    6    7
        '-', '-', '-', 'K', '-', '-', '-', '-',  // 0
        '-', '-', '-', '-', '-', '-', '-', '-',  // 1
        '-', '-', '-', '-', '-', '-', '-', '-',  // 2
        '-', '-', 'R', '-', '-', 'k', '-', '-',  // 3
        '-', '-', '-', '-', '-', '-', '-', 'a',  // 4
        '-', '-', '-', '-', '-', '-', '-', '-',  // 5
        '-', '-', '-', '-', '-', '-', '-', '-',  // 6
        '-', '-', '-', '-', '-', '-', '-', 'r',  // 7
            });
    test.compare(board.move({4, 7}, {3, 7}), false,
            "Not escaping check by Rook");
    board.setBoard({
    //   0    1    2    3    4    5    6    7
        '-', '-', '-', 'K', '-', '-', '-', '-',  // 0
        '-', '-', '-', '-', '-', '-', '-', '-',  // 1
        '-', '-', '-', '-', '-', '-', '-', '-',  // 2
        '-', '-', '-', '-', '-', 'k', '-', '-',  // 3
        '-', '-', '-', '-', '-', '-', '-', 'a',  // 4
        '-', '-', '-', '-', 'N', '-', '-', '-',  // 5
        '-', '-', '-', '-', '-', '-', '-', '-',  // 6
        '-', '-', '-', '-', '-', '-', '-', 'r',  // 7
            });
    test.compare(board.move({4, 7}, {3, 7}), false,
            "Not escaping check by Knight");
    board.setBoard({
    //   0    1    2    3    4    5    6    7
        '-', '-', 'B', 'K', '-', '-', '-', '-',  // 0
        '-', '-', '-', '-', '-', '-', '-', '-',  // 1
        '-', '-', '-', '-', '-', '-', '-', '-',  // 2
        '-', '-', '-', '-', '-', 'k', '-', '-',  // 3
        '-', '-', '-', '-', '-', '-', '-', 'a',  // 4
        '-', '-', '-', '-', '-', '-', '-', '-',  // 5
        '-', '-', '-', '-', '-', '-', '-', '-',  // 6
        '-', '-', '-', '-', '-', '-', '-', 'r',  // 7
            });
    test.compare(board.move({4, 7}, {3, 7}), false,
            "Not escaping check by Bishop");
    board.setBoard({
    //   0    1    2    3    4    5    6    7
        '-', '-', '-', 'K', '-', '-', '-', '-',  // 0
        '-', '-', '-', '-', '-', '-', '-', '-',  // 1
        '-', '-', '-', '-', '-', '-', '-', '-',  // 2
        '-', '-', '-', '-', '-', 'k', '-', '-',  // 3
        '-', '-', '-', '-', '-', '-', '-', 'a',  // 4
        '-', '-', '-', '-', '-', '-', '-', '-',  // 5
        '-', '-', 'Q', '-', '-', '-', '-', '-',  // 6
        '-', '-', '-', '-', '-', '-', '-', 'r',  // 7
            });
    test.compare(board.move({4, 7}, {3, 7}), false,
            "Not escaping check by Queen");

    std::cout << "\t\tCheck Valid Excape" << std::endl;
    board.setBoard({
    //   0    1    2    3    4    5    6    7
        '-', '-', '-', 'K', '-', '-', '-', '-',  // 0
        '-', '-', '-', '-', '-', '-', '-', '-',  // 1
        '-', '-', '-', '-', 'A', '-', '-', '-',  // 2
        '-', '-', '-', '-', '-', 'k', '-', '-',  // 3
        '-', '-', '-', '-', '-', '-', '-', 'a',  // 4
        '-', '-', '-', '-', '-', '-', '-', '-',  // 5
        '-', '-', '-', '-', '-', '-', '-', '-',  // 6
        '-', '-', '-', '-', '-', '-', '-', 'r',  // 7
            });
    test.compare(board.move({3, 5}, {2, 5}), true,
            "Escaping check by Pawn");
    board.setBoard({
    //   0    1    2    3    4    5    6    7
        '-', '-', '-', 'K', '-', '-', '-', '-',  // 0
        '-', '-', '-', '-', '-', '-', '-', '-',  // 1
        '-', '-', '-', '-', '-', '-', '-', '-',  // 2
        '-', '-', 'R', '-', '-', 'k', '-', '-',  // 3
        '-', '-', '-', '-', '-', '-', '-', 'a',  // 4
        '-', '-', '-', '-', '-', '-', '-', '-',  // 5
        '-', '-', '-', '-', '-', '-', '-', '-',  // 6
        '-', '-', '-', '-', '-', '-', '-', 'r',  // 7
            });
    test.compare(board.move({3, 5}, {2, 5}), true,
            "Escaping check by Rook");
    board.setBoard({
    //   0    1    2    3    4    5    6    7
        '-', '-', '-', 'K', '-', '-', '-', '-',  // 0
        '-', '-', '-', '-', '-', '-', '-', '-',  // 1
        '-', '-', '-', '-', '-', '-', '-', '-',  // 2
        '-', '-', '-', '-', '-', 'k', '-', '-',  // 3
        '-', '-', '-', '-', '-', '-', '-', 'a',  // 4
        '-', '-', '-', '-', 'N', '-', '-', '-',  // 5
        '-', '-', '-', '-', '-', '-', '-', '-',  // 6
        '-', '-', '-', '-', '-', '-', '-', 'r',  // 7
            });
    test.compare(board.move({3, 5}, {2, 5}), true,
            "Escaping check by Knight");
    board.setBoard({
    //   0    1    2    3    4    5    6    7
        '-', '-', 'B', 'K', '-', '-', '-', '-',  // 0
        '-', '-', '-', '-', '-', '-', '-', '-',  // 1
        '-', '-', '-', '-', '-', '-', '-', '-',  // 2
        '-', '-', '-', '-', '-', 'k', '-', '-',  // 3
        '-', '-', '-', '-', '-', '-', '-', 'a',  // 4
        '-', '-', '-', '-', '-', '-', '-', '-',  // 5
        '-', '-', '-', '-', '-', '-', '-', '-',  // 6
        '-', '-', '-', '-', '-', '-', '-', 'r',  // 7
            });
    test.compare(board.move({3, 5}, {2, 5}), true,
            "Escaping check by Bishop");
    board.setBoard({
    //   0    1    2    3    4    5    6    7
        '-', '-', '-', 'K', '-', '-', '-', '-',  // 0
        '-', '-', '-', '-', '-', '-', '-', '-',  // 1
        '-', '-', '-', '-', '-', '-', '-', '-',  // 2
        '-', '-', '-', '-', '-', 'k', '-', '-',  // 3
        '-', '-', '-', '-', '-', '-', '-', 'a',  // 4
        '-', '-', '-', '-', '-', '-', '-', '-',  // 5
        '-', '-', 'Q', '-', '-', '-', '-', '-',  // 6
        '-', '-', '-', '-', '-', '-', '-', 'r',  // 7
            });
    test.compare(board.move({3, 5}, {2, 5}), true,
            "Escaping check by Queen");

    test.printResult();
    return test;
}

Test testIfDetectCheckmate(){
    Test test("Test if Checkmate is detected");
    ChessBoard board, saved;
    saved.setBoard({
    //   0    1    2    3    4    5    6    7
        '-', '-', '-', '-', '-', '-', '-', '-',  // 0
        '-', '-', '-', '-', '-', '-', '-', '-',  // 1
        '-', '-', '-', '-', '-', '-', '-', '-',  // 2
        '-', '-', '-', '-', '-', '-', '-', '-',  // 3
        '-', '-', '-', '-', '-', '-', '-', '-',  // 4
        '-', '-', '-', '-', '-', '-', '-', '-',  // 5
        '-', '-', '-', '-', '-', '-', '-', '-',  // 6
        '-', '-', '-', '-', '-', '-', '-', '-',  // 7
            });
    board = saved;

    test.printResult();
    return test;
}




