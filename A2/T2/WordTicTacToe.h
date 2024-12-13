#ifndef T2_WORDTICTACTOE_H
#define T2_WORDTICTACTOE_H

#include "BoardGame_Classes.h"
#include "Methods.h"
#include <map>


template <typename T>
class WordBoard: public Board<T>{
public:
    WordBoard();
    ~WordBoard();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class WordPlayer : public Player<T> {
public:
    WordPlayer (string name, T symbol);
    void getmove(int& x, int& y) ;
};

template <typename T>
class WordRandomPlayer : public RandomPlayer<T>{
public:
    WordRandomPlayer (string name, T symbol);
    void getmove(int &x, int &y);
};

pair<int,int> makeIndex(int n);



template<typename T>
WordBoard<T>::WordBoard() {
    this->rows = 3;
    this->columns = 3;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = T();
        }
    }
    this->n_moves = 0;
}

template<typename T>
WordBoard<T>::~WordBoard() {
    for (int i = 0; i < this -> rows; i++) {
        delete[] this -> board[i];
    }
    delete[] this -> board;
}

template<typename T>
bool WordBoard<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x >= this-> rows || y < 0 || y >= this-> columns || this->board[x][y] != T()){  ///buh
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
void WordBoard<T>::display_board() {
    for (int i = 0; i < this ->rows; ++i) {
        for (int j = 0; j < this -> columns ; ++j) {
            cout<<"  "<<this->board[i][j]<<"  ";
        }
        cout<<endl<<endl;
    }
}

template<typename T>
bool WordBoard<T>::is_win() {
    return false;
}

template<typename T>
bool WordBoard<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template<typename T>
bool WordBoard<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
WordPlayer<T>::WordPlayer(string name, T symbol) : Player<T>(name, symbol) {}


template <typename T>
void WordPlayer<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
WordRandomPlayer<T>::WordRandomPlayer(string name, T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = name;
    this->symbol = symbol;
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void WordRandomPlayer<T>::getmove(int& x, int& y) {
    x = (rand() % this->dimension);  // Random number between 0 and 2
    y = (rand() % this->dimension);  // Random number between 0 and 2
}

#endif