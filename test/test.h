#pragma once
#include <iostream>
#include <vector>
#include "../src/board.h"

class Test{

public: 
    std::string msg;
    Test(std::string message);

    void compare(int expect, int actual, std::string message);
    void compare(std::vector<char> a, std::vector<char> b, std::string msg);
    void printResult();
    int getTotalTestCount();
    int getPassedTestCount();
    static void printTestSuit(std::vector<Test> testSuit);

private:
    int totalTest;
    int passedTest;
    void printCompareResult(std::string msg, bool passed);
};


