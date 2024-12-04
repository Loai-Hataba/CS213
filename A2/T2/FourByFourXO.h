//
// Created by abdal on 03/12/2024.
//

#ifndef FOURBYFOURXO_H
#define FOURBYFOURXO_H
#include <map>
#include "Methods.h"
#include "BoardGame_Classes.h"
static int Gets = 0 ;
static int FX = 0 , FY = 0 ;
// 0 -> first get move (from)
// 1 -> second get move (to)
//// Board Prototype
template<class T>
class FourByFourXO : public Board<T> {
    public:
    FourByFourXO();
    ~FourByFourXO();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
} ;

template<class T>
class FourByFourXO_Player: public Player<T> {
    public:
    FourByFourXO_Player(string name, T symbol);
    void getmove(int &x, int &y);
};

/// Player Prototype

template<class T>
class FourByFourXO_Random: public RandomPlayer<T> {
public:
    FourByFourXO_Random(string name, T symbol);
    void getmove(int &x, int &y);
};

void setType(Player<char>*& player, int choice, string name, char symbol) ;
void TicTacToe4x4GameInfo();
void TicTacToe4x4 ();
//Random Player Protoype
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////Implementation
#include <iomanip>
// Board Implementation
template<class T>
FourByFourXO<T>::FourByFourXO() {
    this->rows = 4 ;
    this->columns = 4  ;
    this->n_moves = 0 ;
    this ->board = new T*[this -> rows];
    for (int i = 0; i < this -> rows; i++) {
        this -> board [i] = new T [this-> columns];
        for (int j = 0; j < this-> columns; j++) {
            this -> board[i][j] = T();
        }
    }
    for (int j = 0; j < 4; j++) {
        if(j % 2 == 0) {
            this->board[0][j] = 'O';
            this->board[3][j+1] = 'O';
        }
        else {
            this->board[0][j] = 'X';
            this->board[3][j -1 ] = 'X';
        }
    }

    //this -> board[0][0] = 'X';
}

template<class T>
FourByFourXO<T>::~FourByFourXO() {
    for (int i = 0; i < this -> rows; i++) {
        delete [] this->board[i];
    }
    delete [] this->board;
}

template<class T>
bool FourByFourXO<T>::update_board(int x, int y, T symbol) {
    // Case 1: Selecting a token
    if (this->board[x][y] == symbol && Gets == 0) {
        FX = x;
        FY = y;
        Gets = 1;  // Mark that a token has been selected
        cout << "Token selected at (" << FX << ", " << FY << "). Choose an adjacent cell to move." << endl;
        return false;  // Selection is not a move
    }
    // Case 2: Moving the selected token
    else if (Gets == 1 && this->board[x][y] == T()) {
        // Check if the move is to an adjacent cell
        if (abs(FX - x) + abs(FY - y) == 1) {
            this->board[x][y] = this->board[FX][FY];  // Move the token
            this->board[FX][FY] = T();               // Clear the old position
            Gets = 0;  // Reset selection
            this->n_moves++;
            cout << endl << "Token moved to (" << x << ", " << y << ")." << endl;
            return true;  // Move completed
        } else {
            cout << "Invalid move! You can only move to an adjacent cell." << endl;
            return false;  // Invalid move
        }
    }
    // Case 3: Invalid selection or move
    else if (this->board[x][y] != symbol) {
        cout << endl <<"Invalid selection! Choose a cell containing your token (" << symbol << ")." << endl;
        return false;
    }

    // Default case: No action taken
    return false;
}


template<class T>
void FourByFourXO<T>::display_board() {
    cout << endl <<"--------------------------------------------------------------" <<endl;

    for (int i = 0; i < this -> rows; i++) {
        cout << setw(2)<<"||" ;
        for (int j = 0; j < this -> columns; j++) {
            if(this -> board[i][j] == T()) {
                cout << setw(5)<<  "( " << i << "," << j <<" )" <<setw (5) << "||";
            }
            else {
                cout << setw(7)<< this -> board[i][j]  <<setw (8) << "||";
            }
        }
        //cout << endl ;
        cout << endl <<"--------------------------------------------------------------" <<endl;
    }
}

template<class T>
bool FourByFourXO<T>::is_win() {
    // Check rows
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) { // Check 3 cells at a time
            if (this->board[i][j] != T() && this->board[i][j] == this->board[i][j + 1] &&
                this->board[i][j] == this->board[i][j + 2]) {
                return true;
                }
        }
    }

    // Check columns
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 2; i++) { // Check 3 cells at a time
            if (this->board[i][j] != T() && this->board[i][j] == this->board[i + 1][j] &&
                this->board[i][j] == this->board[i + 2][j]) {
                return true;
                }
        }
    }

    // Check main diagonal (\)
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (this->board[i][j] != T() && this->board[i][j] == this->board[i + 1][j + 1] &&
                this->board[i][j] == this->board[i + 2][j + 2]) {
                return true;
                }
        }
    }
    // Check anti-diagonal (/)
    for (int i = 0; i < 2; i++) {
        for (int j = 2; j < 4; j++) {
            if (this->board[i][j] != T() && this->board[i][j] == this->board[i + 1][j - 1] &&
                this->board[i][j] == this->board[i + 2][j - 2]) {
                return true;
                }
        }
    }

    return false;
}

template<class T>
bool FourByFourXO<T>::is_draw() {
    return !is_win() && this->n_moves == 2011   ;
}

template<class T>
bool FourByFourXO<T>::game_is_over() {
    return is_win() || is_draw() ;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///Player Defenition
template<class T>
FourByFourXO_Player<T>::FourByFourXO_Player(string name, T symbol): Player<T> (name ,symbol)  {
}

template<class T>
void FourByFourXO_Player<T>::getmove(int &x, int &y) {
    string Message = ( Gets == 0 ) ? " ) Please select the cell you want to move from  :  "  : ") Please select the cell you want to move to  :" ;
    cout << " ( "<<this -> getname() <<Message <<endl;
    x =  getValidIndex( "the x index : " , 0 , 3 );
    y =  getValidIndex( "the y index : " , 0 , 3 );
}

template<class T>
FourByFourXO_Random<T>::FourByFourXO_Random(string name, T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 4;
    this->name = name ;
    this->symbol = symbol; // Store the player's symbol
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}

template<class T>
void FourByFourXO_Random<T>::getmove(int &x, int &y) {
    y = rand() % this->dimension ; // Random number between 0 and 3
    x = rand() % this->dimension  ;
}


#endif //FOURBYFOURXO_H
