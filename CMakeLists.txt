cmake_minimum_required(VERSION 3.26)
project(tetris)

set(CMAKE_CXX_STANDARD 14)


add_executable(tetris
        include/TetrisColor.h
        src/TetrisInput.cpp
        src/TetrisGame.cpp

        src/main.cpp
        src/TetrisStart.cpp
        src/TetrisInterface.cpp
        src/TetrisBlock.cpp


)
