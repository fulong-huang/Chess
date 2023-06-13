#include "test.h"

Test::Test(std::string message){
    this->totalTest = 0;
    this->passedTest = 0;
    this->msg = message;
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

void Test::printResult(){
    std::cout << "\n" << this->msg << ": " <<
        this->passedTest << "/" << this->totalTest << 
        "\n\n";
}


void Test::printCompareResult(std::string msg, bool passed){
    std::string outString = 
        "    Test Case " + std::to_string(this->totalTest) +  ": " + msg;
    int filterLen = 80 - outString.size();
    char fillingChar = '-';
    if(this->totalTest % 3 == 1){
        fillingChar = '.';
    }
    else if(this->totalTest % 3 == 2){
        fillingChar = '~';
    }
    for(int i = 0; i < filterLen; i++){
        outString += fillingChar;
    }

    if(passed){
        outString += "   PASSED   ";
    }
    else{
        outString += "===FAILED===";
    }
    std::cout << outString << "\n";
}

int Test::getTotalTestCount(){
    return this->totalTest;
}
int Test::getPassedTestCount(){
    return this->passedTest;
}

void Test::printTestSuit(std::vector<Test> testSuit){
    std::string currMsg = "\n\n";
    for(int i = 0; i < 89; i++){
        currMsg += '=';
    }
    currMsg += '\n';
    for(int i = 0; i < 40; i++){
        currMsg += '=';
    }
    currMsg += " SUMMARY ";
    for(int i = 0; i < 40; i++){
        currMsg += '=';
    }
    currMsg += '\n';
    for(int i = 0; i < 89; i++){
        currMsg += '=';
    }
    std::cout << currMsg << "\n" << std::endl;
    int filterLen;
    for(Test t : testSuit){
        currMsg = t.msg;
        filterLen = 80 - currMsg.size();
        for(int i = 0; i < filterLen; i++){
            currMsg += '-';
        }
        std::cout << currMsg << "   " << 
            t.getPassedTestCount() * 100 / t.getTotalTestCount() <<
            "%" << std::endl;
    }
    std::cout << "\n\n";
}

