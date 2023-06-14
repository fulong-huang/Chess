#include <cstdlib>
#include <iostream>
#include "test/testBasicMovement.h"
#include "test/testMovementWhileInCheck.h"
#include "test/testSpecialMoves.h"

int main(int argc, char* argv[]){

    testBasicMovements();

    testMovementWhileInCheck();

    testSpecialMoves();

    return EXIT_SUCCESS;
}

