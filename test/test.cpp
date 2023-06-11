#include "test.h"


void runTests(){
    testChessBoard();
}


Test::Test(std::string message){
    this->totalTest = 0;
    this->passedTest = 0;
    int paddingLen = 92 - message.size();
    std::string padding = "";
    for(int i = 0; i < paddingLen; i += 2){
        padding += '=';
    }
    std::string title = padding + message + padding;
    std::cout << "\n" << title << "\n";
}

void Test::compare(int expect, int actual, std::string message){
    this->totalTest++;

    if(expect == actual){
        this->passedTest++;
        printCompareResult(message, true);
    }
    else{
        printCompareResult(message, false);
    }
}

void Test::compare(std::vector<char> a, std::vector<char> b, std::string msg){
    this->totalTest++;
    if(a.size() != b.size()){
        printCompareResult(msg, false);
        return;
    }
    for(int i = 0; i < a.size(); i++){
        if(a[i] != b[i]){
            printCompareResult(msg, false);
            return;
        }
    }
    printCompareResult(msg, true);
    this->passedTest++;
}

void Test::printResult(std::string message){
    std::cout << message << 
        this->passedTest << "/" << this->totalTest << 
        "\n\n";
}


void Test::printCompareResult(std::string msg, bool passed){
    std::string outString = 
        "    Test Case " + std::to_string(this->totalTest) +  ": " + msg;
    int filterLen = 80 - outString.size();
    for(int i = 0; i < filterLen; i++){
        outString += '-';
    }

    if(passed){
        outString += "   PASSED   ";
    }
    else{
        outString += "===FAILED===";
    }
    std::cout << outString << "\n";
}
