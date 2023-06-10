#include "test.h"


void runTests(){
    testChessBoard();
}


Test::Test(std::string message){
    this->totalTest = 0;
    this->passedTest = 0;
    std::cout << "=====" << message << "=====" << std::endl;
}

void Test::test(int expect, int actual, std::string message){
    this->totalTest++;
    std::cout << "    Test case: " << message;
    if(expect == actual){
        std::cout << " PASSED!!!\n";
        this->passedTest++;
    }
    else{
        std::cout << "--- FAILED ---\n";
    }
}

void Test::compare(std::vector<char> a, std::vector<char> b, std::string msg){
    std::cout << "    Test case: " << msg;
    this->totalTest++;
    if(a.size() != b.size()){
        std::cout << "--- FAILED ---\n";
        return;
    }
    for(int i = 0; i < a.size(); i++){
        if(a[i] != b[i]){
            std::cout << "--- FAILED ---\n";
            return;
        }
    }
    std::cout << " PASSED!!!\n";
    this->passedTest++;
}

void Test::printResult(std::string message){
    std::cout << message << this->passedTest << "/" << this->totalTest << "\n";
}

