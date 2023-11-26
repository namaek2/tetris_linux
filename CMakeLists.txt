cmake_minimum_required(VERSION 3.26)
project(tetris)

set(CMAKE_CXX_STANDARD 14)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})


add_executable(tetris
        include/TetrisTerminal.h
        src/TetrisInput.cpp
        include/TetrisBlock.h
        src/TetrisBlock.cpp
        src/TetrisStart.cpp
        include/TetrisColor.h
        src/main.cpp
)


target_link_libraries(tetris ${CURSES_LIBRARIES})
