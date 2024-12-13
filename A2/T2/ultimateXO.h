#ifndef _ULTIMATEXO_H
#define _ULTIMATEXO_H

#include "BoardGame_classes.h"
static vector<int> moveCheck(9, false);

template <typename T>
class UltimateBoard : public Board<T>
{

public:
    map<int, char> mapBoard = {{0, '0'}, {1, '0'}, {2, '0'}, {3, '0'}, {4, '0'}, {5, '0'}, {6, '0'}, {7, '0'}, {8, '0'}}; // completed a 3x3 section in the board and who won
    UltimateBoard();
    bool update_board(int x, int y, T symbol);
    void display_board();
    void singleWin(int x, int y);
    void countSections(int x, int y, int section);
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class UltimatePlayer : public Player<T>
{
public:
    UltimatePlayer(string name, T symbol);
    void getmove(int &x, int &y);
};

template <typename T>
class UltimateRandomPlayer : public RandomPlayer<T>
{
public:
    UltimateRandomPlayer(T symbol);
    void getmove(int &x, int &y);
};

#include <iostream>
#include <map>
#include <iomanip>
#include <vector>
using namespace std;

template <typename T>
UltimateBoard<T>::UltimateBoard()
{
    this->n_moves = 0;
    this->rows = this->columns = 9;
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
bool UltimateBoard<T>::update_board(int x, int y, T symbol)
{
    if (x == -1 && y == -1)
        return true;
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
        singleWin(x, y);
        return true;
    }
    return false;
}

template <typename T>
void UltimateBoard<T>::display_board()
{
    cout << endl;
    int width = 80;
    int boardWidth = this->columns * 6 + 1 + (this->columns / 3) * 2;
    int padding = (width - boardWidth) / 2;

    for (int i = 0; i < this->rows; i++)
    {
        if (i % 3 == 0 && i != 0)
        {
            cout << string(padding, ' ');
            for (int k = 0; k < this->columns; k++)
            {
                cout << "------";
                if ((k + 1) % 3 == 0 && k + 1 != this->columns)
                    cout << "--";
            }
            cout << "=" << endl;
        }

        cout << string(padding, ' ') << "|";
        for (int j = 0; j < this->columns; j++)
        {
            if (this->board[i][j] == 0) // Empty cell
                cout << "     |";
            else
                cout << "  " << this->board[i][j] << "  |";

            if ((j + 1) % 3 == 0 && j + 1 != this->columns)
                cout << "|";
        }
        cout << "\n";
        cout << string(padding, ' ');
        for (int k = 0; k < this->columns; k++)
        {
            cout << "------";
            if ((k + 1) % 3 == 0 && k + 1 != this->columns)
                cout << "--";
        }
        cout << "-" << endl;
    }

    cout << "\n~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.\n";
}

template <typename T>
void UltimateBoard<T>::countSections(int x, int y, int section)
{
    if (mapBoard[section] != '0') // section is already finished no need to check it again
        return;
    for (int i = y; i < y + 3; i++)
    {
        for (int j = x; j < x + 3; j++)
        {
            if (i > y && j > x) // Inner cells Npt used for checking
                continue;
            if (this->board[i][x] == this->board[i][x + 1] && this->board[i][x] == this->board[i][x + 2] && this->board[i][x] != '\0') // Horizontal check
            {
                mapBoard[section] = this->board[i][x];
                moveCheck[section] = true;
                cout << "1-Section: " << section << " is now won by (" << this->board[y][x] << ")" << endl;
                return;
            }
            else if (this->board[y][j] == this->board[y + 1][j] && this->board[y][j] == this->board[y + 2][j] && this->board[y][j] != '\0') // Vertical check
            {
                mapBoard[section] = this->board[y][j];
                moveCheck[section] = true;

                cout << "2-Section: " << section << " is now won by " << this->board[y][x] << endl;
                return;
            }
            else if (this->board[y][x] == this->board[y + 1][x + 1] && this->board[y][x] == this->board[y + 2][x + 2] && this->board[y][x] != '\0') // Forward diagonal check
            {
                mapBoard[section] = this->board[y][x];
                moveCheck[section] = true;

                cout << "3-Section: " << section << " is now won by " << this->board[y][x] << endl;
                return;
            }
            else if (this->board[y + 2][x] == this->board[y + 1][x + 1] && this->board[y][x + 2] && this->board[y + 2][x] != '\0') // Backward diagonal check
            {
                mapBoard[section] = this->board[y + 2][x];
                moveCheck[section] = true;
                cout << "4-Section: " << section << " is now won by " << this->board[y][x] << endl;
                return;
            }
        }
    }
}

template <typename T>
void UltimateBoard<T>::singleWin(int x, int y)
{
    cout << "Testing y: " << y << " x: " << y << endl;
    if ((y >= 0 || y < 3) && (x >= 0 || x < 3)) // NOTE: section 1 in board
    {
        x = 0;           // Horizontal
        y = 0;           // Vertical
        int section = 0; // 1st section
        countSections(x, y, section);
    }
    if ((y >= 3 && y < 6) && (x >= 0 && x < 3)) // NOTE: section 2 in board
    {
        x = 3;           // Horizontal
        y = 0;           // Vertical
        int section = 1; // 2nd section
        countSections(x, y, section);
    }
    if ((y >= 6 || y < 9) && (x >= 0 || x < 3)) // NOTE: section 3 in board
    {
        x = 6;           // Horizontal
        y = 0;           // Vertical
        int section = 2; // 3rd section
        countSections(x, y, section);
    }
    if ((y >= 0 || y < 3) && (x >= 3 || x < 6)) // NOTE: section 4 in board
    {
        x = 0;           // Horizontal
        y = 3;           // Vertical
        int section = 3; // 4th section
        countSections(x, y, section);
    }
    if ((y >= 3 || y < 6) && (x >= 3 || x < 6)) // NOTE: section 5 in board
    {
        x = 3;           // Horizontal
        y = 3;           // Vertical
        int section = 4; // 5th section
        countSections(x, y, section);
    }
    if ((y >= 6 || y < 9) && (x >= 3 || x < 6)) // NOTE: section 6 in board
    {
        x = 6;           // Horizontal
        y = 3;           // Vertical
        int section = 5; // 6th section
        countSections(x, y, section);
    }
    if ((y >= 0 || y < 3) && (x >= 6 || x < 9)) // NOTE: section 7 in board
    {
        x = 0;           // Horizontal
        y = 6;           // Vertical
        int section = 6; // 7th section
        countSections(x, y, section);
    }
    if ((y >= 3 || y < 6) && (x >= 6 || x < 9)) // NOTE: section 8 in board
    {
        x = 3;           // Horizontal
        y = 6;           // Vertical
        int section = 7; // 8th section
        countSections(x, y, section);
    }
    if ((y >= 6 || y < 9) && (x >= 6 || x < 9)) // NOTE: section 9 in board
    {
        x = 6;           // Horizontal
        y = 6;           // Vertical
        int section = 8; // 9th section
        countSections(x, y, section);
    }
}

template <typename T>
bool UltimateBoard<T>::is_win()
{
    for (int i = 0; i < 9; i += 3)
    {
        // Horizontal check
        if (mapBoard[i] == mapBoard[i + 1] && mapBoard[i] == mapBoard[i + 2] && mapBoard[i] != '0')
            return true;
    }
    // Vertical check
    for (int i = 0; i < 3; i++)
    {
        // Horizontal check
        if (mapBoard[i] == mapBoard[i + 3] && mapBoard[i] == mapBoard[i + 6] && mapBoard[i] != '0')
            return true;
    }
    // Diagonal check
    if (mapBoard[0] == mapBoard[4] && mapBoard[0] == mapBoard[8] && mapBoard[0] != '0')
        return true;
    // Backward Diagonal check
    if (mapBoard[6] == mapBoard[4] && mapBoard[6] == mapBoard[2] && mapBoard[6] != '0')
        return true;
    return false;
}

template <typename T>
bool UltimateBoard<T>::is_draw()
{
    return (this->n_moves == 81 && !is_win());
}

template <typename T>
bool UltimateBoard<T>::game_is_over()
{
    return (is_win() || is_draw());
}

template <typename T>
UltimatePlayer<T>::UltimatePlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void UltimatePlayer<T>::getmove(int &x, int &y)
{
    cout << "\nEnter x and y (0 to 8) separated by spaces: ";
    cin >> x >> y;
    for (int i = 0; i < 9; i += 3)
    {
        for (int j = 0; j < 9; j += 3)
        {
            if ((x >= i && x < i + 3) && (y >= j && y < j + 3)) // finding which section this move is in
            {
                while (moveCheck[((x / 3) * 3 + (y / 3))]) // check if the section is already won
                {
                    cout << "Can't play here this section has already been won\n";
                    cout << "\nEnter x and y (0 to 8) separated by spaces: ";
                    cin >> x >> y;
                }
            }
        }
    }
}

template <typename T>
UltimateRandomPlayer<T>::UltimateRandomPlayer(T symbol) : RandomPlayer<T>(symbol)
{
    this->dimension = 9;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void UltimateRandomPlayer<T>::getmove(int &x, int &y)
{
    // FIXME: add block for already won sections
    x = rand() % this->dimension;
    y = rand() % this->dimension;
    for (int i = 0; i < 9; i += 3)
    {
        for (int j = 0; j < 9; j += 3)
        {
            if ((x >= i && x < i + 3) && (y >= j && y < j + 3)) // finding which section this move is in
            {
                while (moveCheck[((x / 3) * 3 + (y / 3))]) // check if the section is already won
                {
                    cout << "Can't play here this section has already been won ya bot!!\n";
                    x = rand() % this->dimension;
                    y = rand() % this->dimension;
                }
            }
        }
    }
}

#endif