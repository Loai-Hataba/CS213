
#ifndef T2_PYRAMICTICTACTOE_H
#define T2_PYRAMICTICTACTOE_H

#include "BoardGame_Classes.h"
#include "Methods.h"


template <typename T>
class PyramicBoard:public Board<T>{
public:
    PyramicBoard();
    ~PyramicBoard();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class PyramicPlayer : public Player<T> {
public:
    PyramicPlayer (string name, T symbol);
    void getmove(int& x, int& y) ;
};

template <typename T>
class PyramicRandomPlayer : public RandomPlayer<T>{
public:
    PyramicRandomPlayer (string name,T symbol);
    void getmove(int &x, int &y);
};

pair<int,int> makeIndex(int n);

#endif
