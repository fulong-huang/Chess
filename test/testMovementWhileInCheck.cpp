#include "testMovementWhileInCheck.h"

void testMovementWhileInCheck(){
    std::vector<Test> testLists;
    testLists.push_back(testPawnMovement());
}

Test testIfCheckLimitMovement(){
    Test test("Test if Checks Limit Movements");

    return test;
}

Test testIfDetectCheckmate(){
    Test test("Test if Checkmate is detected");

    return test;
}

Test testPawnMovement(){
    Test test("Test Pawn Movement");
    
    ChessBoard board, stage;
    board.setBoard({
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

    return test;
}

Test testRookMovement(){
    Test test("Test Rook Movement");

    return test;
}

Test testKnightMovement(){
    Test test("Test Knight Movement");

    return test;
}

Test testBishopovement(){
    Test test("Test Bishop Movement");

    return test;
}

Test testQueenMovement(){
    Test test("Test Queen Movement");

    return test;
}

Test testKingMovement(){
    Test test("Test King Movement");

    return test;
}

