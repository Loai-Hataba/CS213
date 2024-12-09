//
// Created by abdal on 29/11/2024.
//

#ifndef TICTACTOENUMBERS_H
#define TICTACTOENUMBERS_H
#include "BoardGame_Classes.h"
#include "Methods.h"
/// Board Prototype
template <class T>
class TicTacToeNum_Board : public Board<T>
{
public:
    TicTacToeNum_Board();
    ~TicTacToeNum_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

/// Player Prototype
template <typename T>
class TicTacToeNum_Player : public Player<T>
{
    vector<int> available;

public:
    TicTacToeNum_Player(string name, T symbol);
    void getmove(int &x, int &y);
};
/// Random player Prototype
template <typename T>
class TicTacToeNum_Random : public RandomPlayer<T>
{
    vector<int> available;

public:
    TicTacToeNum_Random(string name, T symbol);
    void getmove(int &x, int &y);
};
/// Game Prototype
int getPlayerSymbol(vector<int> &available);
void setPlayerType(Player<int> *&player, int choice, string name, int symbol);
void NumericalTicTacToe();
void displayNumTicTacToeInfo();
/////////////////////////////////////////////////////////////////////////////////////////
////-----> Implementation
/// Board Implementation
#include <iostream>
#include <iomanip>
#include <cctype>
#include <limits>

template <class T>
TicTacToeNum_Board<T>::TicTacToeNum_Board() // Done
{
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
TicTacToeNum_Board<T>::~TicTacToeNum_Board() // Done
{
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
        cout << "Invalid move! , please choose an empty cell" << endl;
        return false;
    }
    else
    {
        this->board[x][y] = symbol; // Assign symbol to wanted cell
        this->n_moves++;            // Increment Number of moves
        return true;
    }
}

template <class T>
void TicTacToeNum_Board<T>::display_board() // Done
{
    cout << endl
         << " -------------------------------------------------------" << endl;
    for (int i = 0; i < this->rows; i++)
    {
        cout << setw(2) << "|";
        for (int j = 0; j < this->columns; j++)
        {
            cout << setw(6) << this->board[i][j] << setw(4) << "( " << i << "," << j << " )" << setw(3) << "|";
        }
        if (i != 2)
        {
            cout << endl
                 << setw(2) << "|";
            for (int j = 0; j < 3; j++)
            {
                cout << "-----------------|";
                ;
            }
        }
        cout << endl;
    }
    cout << " -------------------------------------------------------" << endl
         << endl;
}

template <class T>
bool TicTacToeNum_Board<T>::is_win() // Done
{
    int sum = 0;
    int filled = 0;
    // For the vertical win
    for (int i = 0; i < this->columns; i++)
    {
        for (int j = 0; j < this->rows; j++)
        {
            if (this->board[j][i] != T())
            {
                sum += this->board[j][i];
                filled++;
            }
        }
        if (sum == 15 && filled == 3)
            return true;
        sum = 0;
        filled = 0;
    }
    ////////////////////////////////////////////////////////
    // For horizontal win
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->columns; j++)
        {
            if (this->board[i][j] != T())
            {
                sum += this->board[i][j];
                filled++;
            }
        }
        if (sum == 15 && filled == 3)
            return true;
        sum = 0;
        filled = 0;
    }
    ////////////////////////////////////////////////////////
    // For anti-diagonal win --> top left to bottom right
    for (int i = 0; i < this->rows; i++)
    {
        if (this->board[i][i] != T())
        {
            sum += this->board[i][i];
            filled++;
        }
    }
    if (sum == 15 && filled == 3)
        return true;
    sum = 0;
    filled = 0;
    ////////////////////////////////////////////////////////
    // For principal diagonal win --> bottom left to top right
    for (int i = this->rows - 1; i >= 0; i--)
    {
        if (this->board[i][this->columns - 1 - i] != T())
        {
            sum += this->board[i][this->columns - 1 - i];
            filled++;
        }
    }
    if (sum == 15 && filled == 3)
        return true;

    return false; // there is no win
}

template <class T>
bool TicTacToeNum_Board<T>::is_draw() // Done
{
    return (this->n_moves == 9 && !this->is_win());
}

template <class T>
bool TicTacToeNum_Board<T>::game_is_over() // Done
{
    return (this->is_win() || this->is_draw());
}
////////////////////////////////////////////////////////////////////
/////Player implementation
template <typename T>
TicTacToeNum_Player<T>::TicTacToeNum_Player(string name, T symbol) : Player<T>(name, symbol)
{
    if (symbol == 0)
    {
        this->available = {2, 4, 6, 8};
    }
    else
    {
        this->available = {1, 3, 5, 7, 9};
    }
}

template <typename T>
void TicTacToeNum_Player<T>::getmove(int &x, int &y)
{
    cout << " ( " << this->getname() << " ) Please enter which cell do you want :  " << endl;
    x = getValidIndex("the x index : ", 0, 2);
    y = getValidIndex("the y index : ", 0, 2);
    // Now time To choose the num
    this->symbol = getPlayerSymbol(this->available);
}

/////////////////////////////////////////////////////////////////////////////////////////////
/// Random Player implementation
template <typename T>
TicTacToeNum_Random<T>::TicTacToeNum_Random(string name, T symbol) : RandomPlayer<T>(symbol)
// Done
{
    this->dimension = 3;
    this->name = name;
    if (symbol == 0)
    {
        this->available = {2, 4, 6, 8};
    }
    else
    {
        this->available = {1, 3, 5, 7, 9};
    }
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}

template <typename T>
void TicTacToeNum_Random<T>::getmove(int &x, int &y) // Done
{
    while (true)
    {
        x = rand() % this->dimension; // Random number between 0 and 2
        if ((x >= 0 && x <= 2))
        {
            break;
        }
    }
    while (true)
    {
        y = rand() % this->dimension; // Random number between 0 and 2
        if ((y >= 0 && y <= 2))
        {
            break;
        }
    }
    this->symbol = getPlayerSymbol(this->available);
}

#endif // TICTACTOENUMBERS_H
