#include <cstdlib>
#include <iostream>
#include "test/testBasicMovement.h"
#include "test/testMovementWhileInCheck.h"

int main(int argc, char* argv[]){

    testBasicMovements();

    testMovementWhileInCheck();

    return EXIT_SUCCESS;
}

