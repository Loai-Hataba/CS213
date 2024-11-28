#ifndef _FOUR_IN_A_ROW_h
#define _FOUR_IN_A_ROW_h

#include "BoardGame_Classes.h"
template <typename T>
class Four_In_A_Row_Board: public Board<T>{
    public:
        Four_In_A_Row_Board();
        ~Four_In_A_Row_Board() ;
        bool update_board(int x, int y, T symbol);
        void display_board();
        bool is_win();
        bool is_draw();
        bool game_is_over();
};
template <typename T>
class Four_In_A_Row_Player : public Player<T>{
public :
    Four_In_A_Row_Player(string name, T symbol);
    void getmove(int &x, int &y);
};

template <typename T> 
class Four_In_A_Row_Random: public RandomPlayer<T>{
    public : 
    Four_In_A_Row_Random(string name, T symbol);
    void getmove(int &x, int &y);
};
/////////////////////////////////////////////////////////////////////
// Implementation
#include <iostream>
#include <iomanip>
#include <cctype>

template <typename T>
Four_In_A_Row_Board<T>::Four_In_A_Row_Board()
{
    this-> rows = 6 ;
    this -> columns = 7 ;
    this->n_moves = 0;
    this -> board = new char * [this -> rows] ;
    for(int i = 0 ; i < 6 ; i++ )
    {
        this->board[i] = new char[this->columns];
        for (int j = 0 ; j < 7 ; j++)
        {
            this->board[i][j] = 0;
        }
    }
}
template <typename T>
Four_In_A_Row_Board<T>::~Four_In_A_Row_Board() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;
}
template <typename T>
bool Four_In_A_Row_Board<T>::update_board(int x, int y, T symbol)
{
    // Adjust for zero-based indexing
    x--;
    y--;
    // Validate the position
    if (x < 0 || y < 0 || x >= this->rows || y >= this->columns || this->board[x][y] != 0)
    {
        return false; // Invalid move
    }
    // Update the board
    this->board[x][y] = symbol;

    // Increment the move count
    n_moves++;
    return true; // Move successful
}

template <typename T >
 void Four_In_A_Row_Board<T>::   display_board(void) 
 {
     for (int i = 0; i <= 5; i++)
     {
         cout << setw(2) << i + 1 << setw(2) << " | ";
         for (int j = 0; j <= 6; j++)
         {
             cout << setw(2) <<this->board[i][j] << setw(2) << "  | ";
         }
         cout << endl
              << "---|";
         for (int j = 1; j <= 7; j++)
         {
             cout << "-----|";
         }
         cout << endl;
     }
     cout << "   |";
     for (int i = 1; i <= 7; i++)
     {
         cout << "  " << i << "  |";
     }
 }

 template <typename T>
 bool Four_In_A_Row_Board<T> :: is_win()
 {
    // For horizontal win 
    for (int i = 0; i <6 ; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            if ( (this -> board[i][j] != 0)  && this->board[i][j] == this->board[i][j+1] &&
                this -> board[i][j+1]== this->board[i][j+2] &&
                this -> board[i][j+2] == this->board[i][j + 3 ] ) return true ;
        }
    }
    // For vertical win 
    for(int i = 0; i < 7; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            if ( this ->board [j][i] != 0 && this->board[j][i] == this->board[j+1][i]
                && this->board[j+1][i] == this -> board[j+2][i] &&
                this -> board[j+2][i] ==  this->board[j + 3][i] ) return true ;
        }
        
    } 
    // For diagonal win

    return false ;
 }
 template <typename T>
 bool Four_In_A_Row_Board<T> :: is_draw()
 {
      return (this -> n_moves == 42 && ! this -> is_win());
 }
 template <typename T>
 bool Four_In_A_Row_Board<T> :: game_is_over()
 {
      return this -> is_win() || this -> is_draw() ;
 }
/// Player Implementations 
 template <typename T>
  Four_In_A_Row_Player<T>::Four_In_A_Row_Player(string name, T symbol)
 {

     this->name = name;
     this->symbol = symbol;
 }

template <typename T>
void Four_In_A_Row_Player<T>::getmove(int &x, int &y)
{
    cout << "Please enter which Column do You want ( 1 -> 7 ) :  " <<endl;
    cout << "The Column is : " ;
    cin >> x ;
    y=0;
}
// Random player implementation
template <typename T>
 Four_In_A_Row_Random<T>::Four_In_A_Row_Random(string name, T symbol)
{
    this->dimension = 7;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}

template <typename T>
void Four_In_A_Row_Random<T>::getmove(int &x, int &y)
{
    x = rand() % this->dimension + 1; // Random number between 1 and 7
    y = 0;  // Always place the move in the first column (column 0)
}
#endif

