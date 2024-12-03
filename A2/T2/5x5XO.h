#ifndef _5X5XO_H

#define _5X5XO_H

#include "BoardGame_classes.h"
#include <map>
#define YELLOW "\033[33m"
#define RESET "\033[0m"

static int c = 0; // turn is checking for 'O'
static bool draw = false;
static bool won = false;

template <typename T>
class XO_Board : public Board<T>
{
private:
    map<char, int> counter;

public:
    XO_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    int countWin();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class XO_Player : public Player<T>
{
public:
    XO_Player(string name, T symbol);
    void getmove(int &x, int &y);
};

template <typename T>
class XO_RandomPlayer : public RandomPlayer<T>
{
public:
    XO_RandomPlayer(T symbol);
    void getmove(int &x, int &y);
};

#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

template <typename T>
XO_Board<T>::XO_Board()
{
    this->n_moves = 0;
    this->rows = this->columns = 5;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++)
        {
            this->board[i][j] = 0;
        }
    }
}

template <typename T>
bool XO_Board<T>::update_board(int x, int y, T symbol)
{
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0))
    {
        if (symbol == 0)
        {
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else
        {
            this->n_moves++;
            this->board[x][y] = symbol;
        }
        return true;
    }
    return false;
}

template <typename T>
void XO_Board<T>::display_board()
{
    cout << endl;
    int consoleWidth = 80;                         // Assuming a standard console width of 80 characters
    int boardWidth = this->columns * 6 + 1;        // Each cell is 5 spaces + 1 for '|' separator
    int padding = (consoleWidth - boardWidth) / 2; // Calculate leading spaces for centering

    for (int i = 0; i < this->rows; i++)
    {
        // Add padding spaces before each row
        cout << string(padding, ' ') << "|";
        for (int j = 0; j < this->columns; j++)
        {
            if (this->board[i][j] == 0) // Empty cell
                cout << "     |";
            else
                cout << "  " << this->board[i][j] << "  |"; // Center-align characters
        }
        cout << "\n";

        // Add padding spaces before the horizontal separator
        cout << string(padding, ' ');
        for (int k = 0; k < this->columns; k++) // Generate horizontal line dynamically
            cout << "------";                   // 6 dashes per column (5 spaces + separator)
        cout << "-";                            // Extra dash for the last separator
        cout << endl;
    }

    // Add padding spaces for the final decorative line
    // cout << string(padding, ' ');
    cout << "\n~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.\n";
}
template <typename T>
int XO_Board<T>::countWin()
{
    // Reset counter for both players
    counter['X'] = 0;
    counter['O'] = 0;
    int temp = 0;
    for (int i = 0; i < 5; i++) // Rows
    {
        for (int j = 0; j < 5; j++) // Columns
        {
            // CHECK ROWS (Horizontal lines)
            if (j <= 2 && this->board[i][j] == this->board[i][j + 1] &&
                this->board[i][j] == this->board[i][j + 2] && this->board[i][j] != '\0')
            {
                counter[this->board[i][j]]++;
                // cout << YELLOW << "1 " << RESET;
            }

            // CHECK COLUMNS (Vertical lines)
            if (i <= 2 && this->board[i][j] == this->board[i + 1][j] &&
                this->board[i][j] == this->board[i + 2][j] && this->board[i][j] != '\0')
            {
                counter[this->board[i][j]]++;
                // cout << YELLOW << "2 " << RESET;
            }

            // CHECK FORWARD DIAGONAL
            if (i <= 2 && j <= 2 && this->board[i][j] == this->board[i + 1][j + 1] &&
                this->board[i][j] == this->board[i + 2][j + 2] && this->board[i][j] != '\0')
            {
                counter[this->board[i][j]]++;
                // cout << YELLOW << "3 " << RESET;
            }

            // CHECK BACKWARD DIAGONAL
            if (i <= 2 && j >= 2 && this->board[i][j] == this->board[i + 1][j - 1] &&
                this->board[i][j] == this->board[i + 2][j - 2] && this->board[i][j] != '\0')
            {
                counter[this->board[i][j]]++;
                // cout << YELLOW << "4 " << RESET;
            }
        }
    }
    // cout << "final X: " << counter['X'] << endl
    //      << "final O: " << counter['O'] << endl;
    int ans = counter['O'] - counter['X'];
    return ans;
}

template <typename T>
bool XO_Board<T>::is_win()
{
    if (this->n_moves == 24)
    {
        int owin = countWin();
        if (!owin)
        {
            draw = true;
            return false;
        }
        if (c) // X Turn
        {
            if (owin > 0) // O Wins
            {
                cout << "O wins & X turn\n";
                c = 0;
                return false;
            }
            else // X Wins
            {
                cout << "X wins & X turn\n";
                won = true;
                return true;
            }
        }
        else // O turn
        {
            if (owin > 0) // O Wins
            {
                cout << "O wins & O turn\n";
                won = true;
                return true;
            }
            else // X Wins
            {
                cout << "X wins & O turn\n";
                c = 1;
                return false;
            }
        }
    }
    return false;
}

template <typename T>
bool XO_Board<T>::is_draw()
{
    return (draw); // NOTE: removed condition && !is_win()
}

template <typename T>
bool XO_Board<T>::game_is_over()
{
    return (won || is_draw());
    // return (is_draw()); FIXME:
}

template <typename T>
XO_Player<T>::XO_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void XO_Player<T>::getmove(int &x, int &y)
{

    cout << "\nEnter x and y (0 to 5) separated by spaces: ";
    cin >> x >> y;
}

template <typename T>
XO_RandomPlayer<T>::XO_RandomPlayer(T symbol) : RandomPlayer<T>(symbol)
{
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void XO_RandomPlayer<T>::getmove(int &x, int &y)
{
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

#endif // _5X5XO_H