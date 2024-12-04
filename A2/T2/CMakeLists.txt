cmake_minimum_required(VERSION 3.29)
project(T2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(T2
    3x3X_O.h
    BoardGame_Classes.h
    Four-in-a-row.h
    main.cpp
    MinMaxPlayer.h
        Four-in-a-row.cpp
        TicTacToeNumbers.cpp
        TicTacToeNumbers.h
        Methods.cpp
        Methods.h
        UltimateTicTacToe.cpp
        UltimateTicTacToe.h
        FourByFourXO.cpp
        FourByFourXO.h)
