cmake_minimum_required(VERSION 3.29)
project(T2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(T2
    3x3X_O.h
    BoardGame_Classes.h
		Connect4.h
		Connect4.cpp
        TicTacToeNumbers.cpp
        TicTacToeNumbers.h
        Methods.cpp
        Methods.h
        FourByFourXO.cpp
        FourByFourXO.h
        PyramicTicTacToe.h
		PyramicTicTacToe.cpp
		WordTicTacToe.h
		WordTicTacToe.cpp
		ultimateXO.cpp
		app.cpp
		Misere3x3XO.cpp
		5x5XO.cpp)
