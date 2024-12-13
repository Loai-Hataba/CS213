#ifndef TICTACTOENUMBERS_H
#define TICTACTOENUMBERS_H
#include "BoardGame_Classes.h"
#include "Methods.h"
static vector <int> Even = { 2 , 4 , 6 , 8 } ;
static vector <int> Odd = { 1 ,3 ,5, 7, 9 } ;
static vector <int> *CurrentSet =  nullptr  ;
static bool IsRandom = false ; // variable to avoid the error messages from random player until a valid play found
/// Board Prototype
template <class T>
class TicTacToeNum_Board : public Board<T>
{
public:
    TicTacToeNum_Board(); // Board constructor
    ~TicTacToeNum_Board();//Board destructor
    bool update_board(int x, int y, T symbol); // Function to update the board if valid move palyed
    void display_board(); // function to display board status
    bool is_win(); // function to check if there is a wining
    bool is_draw(); // function to check if there is a Tie
    bool game_is_over(); // function to indicate is the game over or not
};

/// Player Prototype
template <typename T>
class TicTacToeNum_Player : public Player<T>
{
    vector<int> * ptrHuman;  // Pointer to the current set ( even - odd )
public:
    TicTacToeNum_Player(string name, T symbol); // Human player Constructor
    void getmove(int &x, int &y); // Human player get a valid move funtion
};
/// Random player Prototype
template <typename T>
class TicTacToeNum_Random : public RandomPlayer<T>
{
    vector<int> *ptrRandom  ; // Pointer to the current set ( even - odd )
    int getRandomSymbol(vector< int > & available); // a helper function to get a random number
public:
    TicTacToeNum_Random(string name, T symbol); // Random player constructor
    void getmove(int &x, int &y); // function to get a valid move
};
/// Game Prototype
int getPlayerSymbol(vector<int> &available); // a helper function to get the Number from player's set that he want to play
void setPlayerType(Player<int> *&player, int choice, string name, int symbol); // a helper function indicates player type (Human - Random - AI )
void NumericalTicTacToe(); // the main function of the game
void displayNumTicTacToeInfo(); // function to display game rules
/////////////////////////////////////////////////////////////////////////////////////////
////-----> Implementation
/// Board Implementation
#include <iostream>
#include <iomanip>
#include <cctype>
#include <limits>

template <class T>
TicTacToeNum_Board<T>::TicTacToeNum_Board()
{
    // Build the board and set each component
    //( rows - columns - num of moves - each cell in the board to be empty)
    this->rows = 3;
    this->columns = 3;
    this->n_moves = 0;
    this->board = new T *[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++)
        {
            this->board[i][j] = T();
        }
    }
}

template <class T>
TicTacToeNum_Board<T>::~TicTacToeNum_Board()
{
    // deleting the board from teh memory (to avoid memory leak )
    for (int i = 0; i < this->rows; i++)
    {
        delete[] this->board[i];
    }
    delete[] this->board;
}

template <class T>
bool TicTacToeNum_Board<T>::update_board(int x, int y, T symbol)
{
    // Check if the cell is not empty
    if (this->board[x][y] != T())
    {
        if(!IsRandom)cout << "Invalid move! , please choose an empty cell" << endl;
        return false;
    }
    else
    {
        CurrentSet = (symbol % 2 == 0 ) ? &Even : &Odd;
        CurrentSet -> erase(find (CurrentSet -> begin(), CurrentSet -> end(), symbol));
        this->board[x][y] = symbol; // Assign symbol to wanted cell
        this->n_moves++;            // Increment Number of moves
        return true;
    }
}

template<class T>
void TicTacToeNum_Board<T>::display_board() {
    cout << "\n============== Numerical Tic Tac Toe Board ==============\n";

    for (int i = 0; i < this->rows; i++) {
        cout << "   +---------+---------+---------+" << endl;
        cout << "   |";
        for (int j = 0; j < this->columns; j++) {
            // Display cell value or empty space if default
            if (this->board[i][j] != T()) {
                cout << setw(5) << this->board[i][j] << setw(5) << "|";
            } else {
                cout << setw(10) << "|";
            }
        }
        cout << endl;
        cout << "   |";
        for (int j = 0; j < this->columns; j++) {
            // Display coordinates
            cout << " ( " << i << "," << j << " ) |";
        }
        cout << endl;
    }
    cout << "   +---------+---------+---------+" << endl;
    cout << "=========================================================\n\n";
}

template<class T>
bool TicTacToeNum_Board<T>::is_win() {
    int DiagonalSum = 0, AntiDiagonalSum = 0;
    // Loop through rows and columns
    for (int i = 0; i < this->rows; i++) {
        int VerticalSum = 0;   // Reset vertical sum for each column
        int HorizontalSum = 0; // Reset horizontal sum for each row
        int VerticalFilled = 0; // Reset vertical filled count for each column
        int HorizontalFilled = 0; // Reset horizontal filled count for each row
        for (int j = 0; j < this->columns; j++) {
            // Check vertical sums
            if (this->board[j][i] != T()) {
                VerticalSum += this->board[j][i];
                VerticalFilled++;
            }
            // Check horizontal sums
            if (this->board[i][j] != T()) {
                HorizontalSum += this->board[i][j];
                HorizontalFilled++;
            }
        }
        // Check if a vertical or horizontal win is found
        if ((VerticalSum == 15 && VerticalFilled == 3) || (HorizontalSum == 15 && HorizontalFilled == 3))
            return true;

        // Accumulate diagonal sums
        if (this->board[i][i] != T()) {
            DiagonalSum += this->board[i][i];
        }
        if (this->board[i][this->columns - 1 - i] != T()) {
            AntiDiagonalSum += this->board[i][this->columns - 1 - i];
        }
    }

    // Check diagonal wins after loop
    if ((DiagonalSum == 15 ) || (AntiDiagonalSum == 15))
        return true;
    // No win condition met
    return false;
}

template <class T>
bool TicTacToeNum_Board<T>::is_draw()
{
    return (this->n_moves == 9 && !this->is_win());
}

template <class T>
bool TicTacToeNum_Board<T>::game_is_over()
{
    return (this->is_win() || this->is_draw());
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////Player implementation
template <typename T>
TicTacToeNum_Player<T>::TicTacToeNum_Player(string name, T symbol) : Player<T>(name, symbol)
{
   ptrHuman = (symbol == 0 ) ? &Odd : &Even;
 }

template <typename T>
void TicTacToeNum_Player<T>::getmove(int &x, int &y)
{
    cout << " ( " << this->getname() << " ) Please enter which cell do you want :  " << endl;
    x = getValidIndex("the x index : ", 0, 2);
    y = getValidIndex("the y index : ", 0, 2);
    this->symbol = getPlayerSymbol(*ptrHuman );
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Random Player implementation
template <typename T>
TicTacToeNum_Random<T>::TicTacToeNum_Random(string name, T symbol) : RandomPlayer<T>(symbol)
// Done
{
    this->dimension = 3;
    this->name = name;
    ptrRandom = (symbol == 0 ) ? &Odd : &Even;
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}
template<typename T>
int TicTacToeNum_Random<T>::getRandomSymbol(vector<int> &available) {
    int choice = rand() % available.size();
    return available[choice];
}

template <typename T>
void TicTacToeNum_Random<T>::getmove(int &x, int &y) // Done
{
    while (true)
    {
        x = rand() % this->dimension; // Random number between 0 and 2
        if ((x >= 0 && x <= 2)) break; // valid x axis
    }
    while (true)
    {
        y = rand() % this->dimension; // Random number between 0 and 2
        if ((y >= 0 && y <= 2)) break; // valid y axis
    }
    this->symbol = getRandomSymbol(*ptrRandom );
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // TICTACTOENUMBERS_H
