#ifndef _FOUR_IN_A_ROW_h
#define _FOUR_IN_A_ROW_h

#include "BoardGame_Classes.h"
#include "Methods.h"

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
    Four_In_A_Row_Player(string name, T symbol) ;
    void getmove(int &x, int &y);
};

template <typename T> 
class Four_In_A_Row_Random: public RandomPlayer<T>{
    public : 
    Four_In_A_Row_Random(string name, T symbol);
    void getmove(int &x, int &y);
};
/// Game Prototype
void Connect_Four_Game ( ) ;
void setPlayerType(Player<char>*& player, int choice, string name, char symbol) ;
void displayConnect4GameInfo();
/////////////////////////////////////////////////////////////////////
// Implementation
#include <iostream>
#include <iomanip>
#include <cctype>
#include <limits>

template <typename T>
Four_In_A_Row_Board<T>::Four_In_A_Row_Board() // Done
{
    this-> rows = 6 ;
    this -> columns = 7 ;
    this->n_moves = 0;
    this -> board = new T* [this -> rows] ;
    for(int i = 0 ; i < this -> rows ; i++ )
    {
        this->board[i] = new T[this->columns]; // Allocate memory for each row
        for (int j = 0 ; j < this -> columns  ; j++)
        {
            this->board[i][j] = T();
        }
    }
}

template <typename T>
Four_In_A_Row_Board<T>::~Four_In_A_Row_Board() { //Done
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i]; //Delete each row  (and the memory it has )
    }
    delete[] this->board; // delete the pointer
}

template <typename T>
bool Four_In_A_Row_Board<T>::update_board(int x, int y, T symbol)
{
    // Adjust for zero-based indexing
    y-- ;
    //Checking if the column is  full
    if(this -> board [0][y] != T() ) {
        cout << "Invalid Move The column is full "<<endl;
        return false;
    }
    // Find the lowest empty row in the specified column
    for (int i = this->rows - 1; i >= 0; i--) {
        if (this->board[i][y] == T()) {
            this->board[i][y] = symbol; // Update the board
            this->n_moves++;           // Increment the move count
            return true;               // Move successful
        }
    }
    // This should never be reached due to the column-full check
    return false;
}

template <typename T >
 void Four_In_A_Row_Board<T>::   display_board() //Done
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
    cout << endl << endl ;
 }

 template <typename T>
 bool Four_In_A_Row_Board<T> :: is_win()
 {
    // For horizontal win 
    for (int i = 0; i <6 ; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            if ( (this -> board[i][j] != T())  && this->board[i][j] == this->board[i][j+1] &&
                this -> board[i][j+1]== this->board[i][j+2] &&
                this -> board[i][j+2] == this->board[i][j + 3 ] ) return true ;
        }
    }
    // For vertical win 
    for(int i = 0; i < 7; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            if ( this ->board [j][i] != T() && this->board[j][i] == this->board[j+1][i]
                && this->board[j+1][i] == this -> board[j+2][i] &&
                this -> board[j+2][i] ==  this->board[j + 3][i] ) return true ;
        }
        
    } 
    // For  Principal diagonal win
    for (int i = 0; i <this->rows -3  ; i++)
    {
        for (size_t j = 0; j < this -> columns -3 ; j++)
        {
            if ( (this -> board[i][j] !=T())  && this->board[i][j] == this->board[i+1][j+1] &&
                this -> board[i+1][j+1]== this->board[i+2][j+2] &&
                this -> board[i+2][j+2] == this->board[i+3][j + 3 ] ) return true ;
        }
    }

    // For Anti-diagonal win
    for (int i = 0; i < this->rows - 3; i++) {  // Rows limit adjusted to avoid out-of-bounds access
        for (int j = this->columns - 1; j >= 3; j--) {  // Start from the last column and check leftward
            if (this->board[i][j] != T() &&  // Ensure the current cell is not empty
                this->board[i][j] == this->board[i+1][j-1] &&
                this->board[i+1][j-1] == this->board[i+2][j-2] &&
                this->board[i+2][j-2] == this->board[i+3][j-3]) {  // Check for the anti-diagonal match
                return true;  // If an anti-diagonal is found, return true
                }
        }
    }

    return false ;
 }
 template <typename T>
 bool Four_In_A_Row_Board<T> :: is_draw() //Done
 {
      return (this -> n_moves == 42 && ! this -> is_win());
 }
 template <typename T>
 bool Four_In_A_Row_Board<T> :: game_is_over()// Done
 {
      return (this -> is_win() || this -> is_draw() ) ;
 }
//////////////////////////////////////////////////////////////////////
/// Player Implementations 
 template <typename T>
  Four_In_A_Row_Player<T>::Four_In_A_Row_Player(string name, T symbol): Player<T> (name ,symbol){} // Done

template <typename T>
void Four_In_A_Row_Player<T>::getmove(int &x, int &y) // Done
{
    y = getValidIndex( "Please enter which Column do You want ( 1 -> 7 ) :  \n""The Column is : " , 1 , 7 ) ;
    x = 0 ;
}
// Random player implementation
template <typename T>
 Four_In_A_Row_Random<T>::Four_In_A_Row_Random(string name, T symbol) : RandomPlayer<T>(symbol)
{
    this->dimension = 7;
    this->name = name ;
    this->symbol = symbol; // Store the player's symbol
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}

template <typename T>
void Four_In_A_Row_Random<T>::getmove(int &x, int &y)
{
    y = rand() % this->dimension + 1; // Random number between 1 and 7
    x = 0;
}
#endif

