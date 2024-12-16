#ifndef _Connect4_h
#define _Connect4_h
#include "BoardGame_Classes.h"
#include "A2_S20_Task23_20230553_20230231_20230121_Methods.h"
static bool Connect4_ISRandom = false; // variable to avoid the error messages from random player until a valid play found
template <typename T>
class Connect4_Board : public Board<T>
{
    bool dropToken(int column, T token); // A helper function to drop the token in the specified column
public:
    Connect4_Board();                          // Board constructor
    ~Connect4_Board();                         // Board destructor
    bool update_board(int x, int y, T symbol); // Function to update the board if there is a valid play
    void display_board();                      // //Function to display board status
    bool is_win();                             // Function to check if  there is a winning
    bool is_draw();                            // Function to check tif there is a Tie
    bool game_is_over();                       // Function to check if the game is over or not
};
// Human Player prototype
template <class T>
class Connect4_Human : public Player<T>
{
public:
    Connect4_Human(string name, T symbol); // Human player constructor
    void getmove(int &x, int &y);          // function to get a valid play from the human player
};
//// Random player Prototype
template <class T>
class Connect4_Random : public RandomPlayer<T>
{
public:
    Connect4_Random(string name, T symbol); // Random player constructor
    void getmove(int &x, int &y);           // function to get a valid play from the random player
};
/// Game functions  Prototype
void Connect4();
void Connect4SetPlayerType(Player<char> *&player, int choice, string name, char symbol);
void displayConnect4GameInfo();
/////////////////////////////////////////////////////////////////////
// Implementation

template <typename T>
Connect4_Board<T>::Connect4_Board() // Done
{
    // 1- assign the board 's dimensions & number of moves
    // 2-  build the board and make the cells empty
    this->rows = 6;
    this->columns = 7;
    this->n_moves = 0;
    this->board = new T *[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new T[this->columns]; // Allocate memory for each row
        for (int j = 0; j < this->columns; j++)
        {
            this->board[i][j] = T();
        }
    }
}

template <typename T>
Connect4_Board<T>::~Connect4_Board()
{
    for (int i = 0; i < this->rows; i++)
    {
        delete[] this->board[i]; // Delete each row  (and the memory it has )
    }
    delete[] this->board; // delete the pointer
}
template <typename T>
bool Connect4_Board<T>::dropToken(int column, T token)
{
    // Checking if the column is  full
    if (this->board[0][column] != T())
    {
        if (!Connect4_ISRandom)
            cout << "Invalid Move The column is full " << endl;
        return false;
    }

    // Find the lowest empty row in the specified column
    for (int i = this->rows - 1; i >= 0; i--)
    {
        if (this->board[i][column] == T())
        {
            this->board[i][column] = token; // Update the board
            this->n_moves++;                // Increment the move count
            return true;                    // Move successful
        }
    }
    return false;
}

template <typename T>
bool Connect4_Board<T>::update_board(int x, int y, T symbol)
{
    // Adjust for zero-based indexing
    y--;
    if (dropToken(y, symbol))
    {
        Connect4_ISRandom = false;
        return true;
    }
    return false;
}

template <typename T>
void Connect4_Board<T>::display_board()
{
    cout << "\n==================== Connect Four Board ====================\n";

    // Loop through each row of the board
    for (int i = 0; i < 6; i++)
    {
        cout << "   +------+------+------+------+------+------+------+" << endl;
        cout << setw(2) << i + 1 << " |"; // Display row number
        for (int j = 0; j < 7; j++)
        {
            // Display cell value or empty space
            if (this->board[i][j] != T())
            {
                cout << setw(4) << this->board[i][j] << setw(3) << "|";
            }
            else
            {
                cout << setw(7) << "|";
            }
        }
        cout << endl;
    }

    // Bottom border
    cout << "   +------+------+------+------+------+------+------+" << endl;
    // Column headers
    cout << "     ";
    for (int j = 1; j <= 7; j++)
    {
        cout << "  " << j << "    ";
    }
    cout << "\n===========================================================\n\n";
}

template <typename T>
bool Connect4_Board<T>::is_win()
{
    // For horizontal win
    for (int i = 0; i < 6; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            if ((this->board[i][j] != T()) && this->board[i][j] == this->board[i][j + 1] &&
                this->board[i][j + 1] == this->board[i][j + 2] &&
                this->board[i][j + 2] == this->board[i][j + 3])
                return true;
        }
    }
    // For vertical win
    for (int i = 0; i < 7; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            if (this->board[j][i] != T() && this->board[j][i] == this->board[j + 1][i] && this->board[j + 1][i] == this->board[j + 2][i] &&
                this->board[j + 2][i] == this->board[j + 3][i])
                return true;
        }
    }
    // For Principal diagonal win
    for (int i = 0; i < this->rows - 3; i++)
    {
        for (size_t j = 0; j < this->columns - 3; j++)
        {
            if ((this->board[i][j] != T()) && this->board[i][j] == this->board[i + 1][j + 1] &&
                this->board[i + 1][j + 1] == this->board[i + 2][j + 2] &&
                this->board[i + 2][j + 2] == this->board[i + 3][j + 3])
                return true;
        }
    }
    // For Anti-diagonal win
    for (int i = 0; i < this->rows - 3; i++)
    { // Rows limit adjusted to avoid out-of-bounds access
        for (int j = this->columns - 1; j >= 3; j--)
        { // Start from the last column and check leftward
            if (this->board[i][j] != T() &&
                this->board[i][j] == this->board[i + 1][j - 1] &&
                this->board[i + 1][j - 1] == this->board[i + 2][j - 2] &&
                this->board[i + 2][j - 2] == this->board[i + 3][j - 3])
            {                // Check for the anti-diagonal match
                return true; // There is an anti-diagonal win
            }
        }
    }

    return false; // There is no winning found
}
template <typename T>
bool Connect4_Board<T>::is_draw()
{
    return (this->n_moves == 42 && !this->is_win());
}
template <typename T>
bool Connect4_Board<T>::game_is_over() // Done
{
    return (this->is_win() || this->is_draw());
}
//////////////////////////////////////////////////////////////////////
/// Player Implementations
template <typename T>
Connect4_Human<T>::Connect4_Human(string name, T symbol) : Player<T>(symbol)
{
    this->name = name;
}
template <typename T>
void Connect4_Human<T>::getmove(int &x, int &y) // Done
{
    y = getValidIndex("Please enter which Column do You want ( 1 -> 7 ) :  \n"
                      "The Column is : ",
                      1, 7);
    x = 0; // We don't need the row index because we're just dropping the tokens
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Random player implementation
template <typename T>
Connect4_Random<T>::Connect4_Random(string name, T symbol) : RandomPlayer<T>(symbol)
{
    this->dimension = 7;
    this->name = name;
    this->symbol = symbol;                     // Store the player's symbol
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}

template <typename T>
void Connect4_Random<T>::getmove(int &x, int &y)
{
    y = rand() % this->dimension + 1; // Random number between 1 and 7 ( for the column )
    x = 0;                            // also we don't need the row index
    Connect4_ISRandom = true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
