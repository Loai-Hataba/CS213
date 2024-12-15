cmake_minimum_required(VERSION 3.24.2)
project(T2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(T2
    3x3X_O.h
    BoardGame_Classes.h
		Connect4.h
    	MinMaxPlayer.h
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
		app.cpp)
