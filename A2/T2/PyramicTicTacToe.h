#ifndef T2_PYRAMICTICTACTOE_H
#define T2_PYRAMICTICTACTOE_H

#include "BoardGame_Classes.h"
#include <map>


template <typename T>
class PyramidBoard: public Board<T>{
public:
    PyramidBoard();
    ~PyramidBoard();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class PyramidPlayer : public Player<T> {
public:
    PyramidPlayer (string name, T symbol);
    void getmove(int& x, int& y) ;
};

template <typename T>
class PyramidRandomPlayer : public RandomPlayer<T>{
public:
    PyramidRandomPlayer (string name, T symbol);
    void getmove(int &x, int &y);
};

void PyramidSetPlayerType(Player<char> *&player, int choice, string name, char symbol);
void PyramidInfo();
void PyramidTicTacToe();
pair<int,int> makeIndex(int n);



template<typename T>
PyramidBoard<T>::PyramidBoard() {
    this->rows = 3;
    this->columns = 5;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = T();
        }
    }
    this->n_moves = 0;
}

template<typename T>
PyramidBoard<T>::~PyramidBoard() {
    for (int i = 0; i < this -> rows; i++) {
        delete[] this -> board[i];
    }
    delete[] this -> board;
}

template<typename T>
bool PyramidBoard<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x >= this-> rows || y < 0 || y >= this-> columns || (x == 0 && (y == 0 || y == 1 || y == 3 ||y == 4 ) || (x == 1 &&( y == 0 ||y == 4))) || this -> board[x][y] != T()){
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
void PyramidBoard<T>::display_board() {
    int cell = 1;
    int l = 2, r = 2;
    for (int i = 0; i < this ->rows; ++i) {
        if (i == 0){
            cout<<"          ";
        }
        if (i == 1){
            cout<<"     ";
        }
        for (int j = l; j <= r ; ++j) {
            if (this->board[i][j] == T()){
                cout<<"  "<<cell<<"  ";
            }
            else cout<<"  "<<this->board[i][j]<<"  ";
            cell++;
        }
        l--;
        r++;
        cout<<endl<<endl;
    }
}

template<typename T>
bool PyramidBoard<T>::is_win() {
    //only 1 vertical case
    if (this->board[0][2] == this->board[1][2] && this->board[1][2] == this->board[2][2] && this->board[0][2] != T()){
        return true;
    }

    if (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != T() ||
        this->board[0][2] == this->board[1][3] && this->board[1][3] == this->board[2][4] && this->board[0][2] != T()){
        return true;
    }

    for (int i = 1; i < 3; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            if (this->board[i][j] == this->board[i][j+1] && this->board[i][j+1] == this->board[i][j+2] && this->board[i][j] != T()){
                return true;
            }
        }
    }
    return false;
}

template<typename T>
bool PyramidBoard<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template<typename T>
bool PyramidBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
PyramidPlayer<T>::PyramidPlayer(string name, T symbol) : Player<T>(name, symbol) {}


template <typename T>
void PyramidPlayer<T>::getmove(int& x, int& y) {
    int n;
    cout<<endl<<this->name << " Please enter number of cell: ";
    cin>>n;
    x = makeIndex(n).first;
    y = makeIndex(n).second;
}

// Constructor for X_O_Random_Player
template <typename T>
PyramidRandomPlayer<T>::PyramidRandomPlayer(string name, T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 9;
    this->name = name;
    this->symbol = symbol;
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void PyramidRandomPlayer<T>::getmove(int& x, int& y) {
    int n = (rand() % this->dimension)+1;  // Random number between 1 and 9
    x = makeIndex(n).first;
    y = makeIndex(n).second;
}

#endif