#ifndef FourByFour_Board_H
#define FourByFour_Board_H
#include "A2_S20_Task23_20230553_20230231_20230121_Methods.h"
#include "BoardGame_Classes.h"
static int selected = 0;
static int FX = 0, FY = 0;
static bool FourByFour_IsRandom = false; // variable to avoid the error messages from random player until a valid play found
// 0 -> first get move (from)
// 1 -> second get move (to)
//// Board Prototype
template <class T>
class FourByFour_Board : public Board<T>
{
private:
    bool hasAdjacentEmpty(int x, int y); // a helper function to check if there is an adjacent cell player can move to
public:
    FourByFour_Board();                        // Board constructor
    ~FourByFour_Board();                       // Board destructor
    bool update_board(int x, int y, T symbol); // Function to update the board status
    void display_board();                      // Function to display board status
    bool is_win();                             //  Function to check the winning
    bool is_draw();                            // Function to check if there is a Tie
    bool game_is_over();                       // Function to indicate if the game is over or not
};
//// Human Player prototype
template <class T>
class FourByFour_Player : public Player<T>
{
public:
    FourByFour_Player(string name, T symbol); // Human Player constructor
    void getmove(int &x, int &y);             // Function to get a valid play from the player
};

/// Random Player Prototype
template <class T>
class FourByFour_Random : public RandomPlayer<T>
{
public:
    FourByFour_Random(string name, T symbol); // Random player constructor
    void getmove(int &x, int &y);             // Function to get a valid play from the player
};

void FourByFourSetPlayerType(Player<char> *&player, int choice, string name, char symbol); // A helper function to set player type (Human - Random - AI)
void TicTacToe4x4GameInfo();                                                               // Function to display game rules
void TicTacToe4x4();                                                                       // The main function for the game
// Random Player Protoype
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////Implementation
// Board Implementation
template <class T>
FourByFour_Board<T>::FourByFour_Board()
{
    // 1- assign the board 's dimensions & number of moves
    // 2-  build the board and assign the 4 tokens of each symbol ( X - O ) to its correct place
    this->rows = 4;
    this->columns = 4;
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

    for (int j = 0; j < 4; j++)
    {
        if (j % 2 == 0)
        {
            this->board[0][j] = 'O';
            this->board[3][j + 1] = 'O';
        }
        else
        {
            this->board[0][j] = 'X';
            this->board[3][j - 1] = 'X';
        }
    }
}

template <class T>
FourByFour_Board<T>::~FourByFour_Board()
{
    // Delete the board ( to avoid memory leak )
    for (int i = 0; i < this->rows; i++)
    {
        delete[] this->board[i];
    }
    delete[] this->board;
}
template <class T>
bool FourByFour_Board<T>::hasAdjacentEmpty(int x, int y)
{
    return ((x > 0 && this->board[x - 1][y] == T()) || // Check cell above
            (x < 3 && this->board[x + 1][y] == T()) || // Check cell below
            (y > 0 && this->board[x][y - 1] == T()) || // Check cell to the left
            (y < 3 && this->board[x][y + 1] == T()));  // Check cell to the right
}

template <class T>
bool FourByFour_Board<T>::update_board(int x, int y, T symbol)
{
    // Case 1: Selecting a token
    if (this->board[x][y] == symbol && selected == 0)
    {
        FX = x;
        FY = y;
        if (hasAdjacentEmpty(x, y))
        { // Check cell to the right
            // There is at least one adjacent empty cell
            selected = 1; // Mark that a token has been selected
            cout << "Token selected at (" << FX << ", " << FY << "). Choose an adjacent cell to move." << endl;
        }
        else
        {
            if (!FourByFour_IsRandom)
                cout << "Token selected at (" << FX << ", " << FY << ")"
                                                                     ".Has no adjacent empty cell please choose another one"
                     << endl;
        }
        return false;
    }
    // Case 2: Moving the selected token
    else if (selected == 1 && this->board[x][y] == T())
    {
        // Check if the move is to an adjacent cell
        if (abs(FX - x) + abs(FY - y) == 1)
        {
            this->board[x][y] = this->board[FX][FY]; // Move the token
            this->board[FX][FY] = T();               // Clear the old position
            selected = 0;                            // Reset selection
            this->n_moves++;
            cout << endl
                 << "Token moved to (" << x << ", " << y << ")." << endl;
            FourByFour_IsRandom = false;
            return true; // Move completed
        }
        else
        {
            if (!FourByFour_IsRandom)
                cout << "Invalid move! You can only move to an adjacent cell." << endl;
            return false; // Invalid move
        }
    }
    // Case 3: Invalid selection or move
    else if (this->board[x][y] != symbol)
    {
        if (!FourByFour_IsRandom)
            cout << endl
                 << "Invalid selection! Choose a cell containing your token (" << symbol << ")." << endl;
        return false;
    }
    // Default case: No action taken
    return false;
}

template <class T>
void FourByFour_Board<T>::display_board()
{
    cout << "\n==================== 4x4 Tic-Tac-Toe Board ====================\n";

    for (int i = 0; i < this->rows; i++)
    {
        cout << "   +------------+------------+------------+------------+" << endl;
        cout << setw(4) << " |"; // Display row number
        for (int j = 0; j < this->columns; j++)
        {
            if (this->board[i][j] == T())
            {
                // Display coordinates for empty cells
                cout << setw(4) << " ( " << i << "," << j << " ) " << setw(3) << "|";
            }
            else
            {
                // Display actual token or value for filled cells
                cout << setw(7) << this->board[i][j] << setw(6) << "|";
            }
        }
        cout << endl;
    }
    cout << "   +------------+------------+------------+------------+" << endl;

    cout << "\n==============================================================\n\n";
}

template <class T>
bool FourByFour_Board<T>::is_win()
{

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            /// For Cloumns Win
            if (this->board[j][i] != T() && this->board[j][i] == this->board[j + 1][i] &&
                this->board[j][i] == this->board[j + 2][i])
            {
                return true;
            }
            //// For Rows Win :
            if (this->board[i][j] != T() && this->board[i][j] == this->board[i][j + 1] &&
                this->board[i][j] == this->board[i][j + 2])
            {
                return true;
            }
        }
    }
    // Check main diagonal (\)
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (this->board[i][j] != T() && this->board[i][j] == this->board[i + 1][j + 1] &&
                this->board[i][j] == this->board[i + 2][j + 2])
            {
                return true;
            }
        }
    }
    // Check anti-diagonal (/)
    for (int i = 0; i < 2; i++)
    {
        for (int j = 2; j < 4; j++)
        {
            if (this->board[i][j] != T() && this->board[i][j] == this->board[i + 1][j - 1] &&
                this->board[i][j] == this->board[i + 2][j - 2])
            {
                return true;
            }
        }
    }
    return false; /// There is no win found
}

template <class T>
bool FourByFour_Board<T>::is_draw()
{
    //  Check if any token can move
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            if (this->board[x][y] == 'X' || this->board[x][y] == 'O')
            { // If it's a token
                if (hasAdjacentEmpty(x, y))
                {                 // Check if token can move
                    return false; // Not a draw because valid moves exist
                }
            }
        }
    }

    // If there is no valid moves can be played
    return true;
}

template <class T>
bool FourByFour_Board<T>::game_is_over()
{
    return is_win() || is_draw();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Player Definition
template <class T>
FourByFour_Player<T>::FourByFour_Player(string name, T symbol) : Player<T>(name, symbol)
{
}

template <class T>
void FourByFour_Player<T>::getmove(int &x, int &y)
{
    // message for the first input ( getting the indexes ( of the cell ) to move from )
    // and a message for the second input (getting the (of the cell ) indexes to move to )
    string Message = (selected == 0) ? " ) Please select the cell you want to move from  :  " : ") Please select the cell you want to move to  :";
    cout << " ( " << this->getname() << Message << endl;
    x = getValidIndex("the x index : ", 0, 3);
    y = getValidIndex("the y index : ", 0, 3);
}

template <class T>
FourByFour_Random<T>::FourByFour_Random(string name, T symbol) : RandomPlayer<T>(symbol)
{
    this->dimension = 4;
    this->name = name;
    this->symbol = symbol;                     // Store the player's symbol
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}

template <class T>
void FourByFour_Random<T>::getmove(int &x, int &y)
{
    y = rand() % this->dimension; // Random number between 0 and 3
    x = rand() % this->dimension;
    FourByFour_IsRandom = true;
}

#endif // FourByFour_Board_H
