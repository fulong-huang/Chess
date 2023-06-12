cmake_minimum_required(VERSION 3.8)

Project(CPP_Chess)

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} 
    main.cpp
    src/board.cpp
    test/test.cpp
    test/testBasicMovement.cpp
    test/testMovementWhileInCheck.cpp
)





