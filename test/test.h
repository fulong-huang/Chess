#pragma once
#include <iostream>
#include "../src/board.h"
#include "chessBoardTest.h"

class Test{

public: 
    Test(std::string message);

    void test(int expect, int actual, std::string message);
    void compare(std::vector<char> a, std::vector<char> b, std::string msg);
    void printResult(std::string message);

private:
    int totalTest;
    int passedTest;
};

void runTests();
