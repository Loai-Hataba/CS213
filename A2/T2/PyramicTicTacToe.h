
#ifndef T2_PYRAMICTICTACTOE_H
#define T2_PYRAMICTICTACTOE_H

#include "BoardGame_Classes.h"
#include "Methods.h"
#include <map>


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



template<typename T>
PyramicBoard<T>::PyramicBoard() {
    this->rows = 3;
    this->columns = 5;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = T();
        }
    }
    int cell = 1;
    int l = 2, r = 2;
    for (int i = 0; i < this ->rows; ++i) {
        for (int j = l; j <= r ; ++j) {
            this->board[i][j] = (cell++) + '0';
        }
        l--;
        r++;
    }
    this->n_moves = 0;
}

template<typename T>
PyramicBoard<T>::~PyramicBoard() {
    for (int i = 0; i < this -> rows; i++) {
        delete[] this -> board[i];
    }
    delete[] this -> board;
}

template<typename T>
bool PyramicBoard<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x >= this-> rows || y < 0 || y >= this-> columns || (x == 0 && (y == 0 || y == 1 || y == 3 ||y == 4 ) || (x == 1 &&( y == 0 ||y == 4)))||!isdigit(this->board[x][y])){
        cout<<"Invalid ya brooooooo!!!"<<endl;
        return false;
    }
    else{
        this->board[x][y] = symbol;
        this->n_moves++;
        return true;
    }
}


template<typename T>
void PyramicBoard<T>::display_board() {
    int l = 2, r = 2;
    for (int i = 0; i < this ->rows; ++i) {
        if (i == 0){
            cout<<"          ";
        }
        if (i == 1){
            cout<<"     ";
        }
        for (int j = l; j <= r ; ++j) {
            cout<<"  "<<this->board[i][j]<<"  ";
        }
        l--;
        r++;
        cout<<endl<<endl;
    }
}

template<typename T>
bool PyramicBoard<T>::is_win() {
    //only 1 vertical case
    if (this->board[0][2] == this->board[1][2] && this->board[1][2] == this->board[2][2]){
        return true;
    }

    if (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0]||
        this->board[0][2] == this->board[1][3] && this->board[1][3] == this->board[2][4]){
        return true;
    }

    for (int i = 1; i < 3; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            if (this->board[i][j] == this->board[i][j+1] && this->board[i][j+1] == this->board[i][j+2]){
                return true;
            }
        }
    }
    return false;
}

template<typename T>
bool PyramicBoard<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template<typename T>
bool PyramicBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
PyramicPlayer<T>::PyramicPlayer(string name, T symbol) : Player<T>(name, symbol) {}


template <typename T>
void PyramicPlayer<T>::getmove(int& x, int& y) {
    int n;
    cout << "\nPlease enter number of cell: ";
    cin>>n;
    x = makeIndex(n).first;
    y = makeIndex(n).second;
}

// Constructor for X_O_Random_Player
template <typename T>
PyramicRandomPlayer<T>::PyramicRandomPlayer(string name,T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 9;
    this->name = name;
    this->symbol = symbol;
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void PyramicRandomPlayer<T>::getmove(int& x, int& y) {
    int n = (rand() % this->dimension)+1;  // Random number between 1 and 9
    x = makeIndex(n).first;
    y = makeIndex(n).second;
}

pair<int,int> makeIndex(int n){
    int cell = 1;
    map<int,pair<int,int>>index;
    index[cell++] = make_pair(0,2);
    for (int i = 1; i < 4; ++i) {
        index[cell++] = make_pair(1,i);
    }
    for (int i = 0; i < 6; ++i) {
        index[cell++] = make_pair(2,i);
    }
    return index[n];
}


#endif