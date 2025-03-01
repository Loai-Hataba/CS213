#ifndef T2_WORDTICTACTOE_H
#define T2_WORDTICTACTOE_H

#include "BoardGame_Classes.h"
#include <map>
#include <fstream>
#include <algorithm>

static bool wordIsRandom = false;

template <typename T>
class WordBoard : public Board<T>
{
public:
    WordBoard();
    ~WordBoard();
    vector<string> dic;
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class WordPlayer : public Player<T>
{
public:
    WordPlayer(string name, T symbol);
    void getmove(int &x, int &y);
};

template <typename T>
class WordRandomPlayer : public RandomPlayer<T>
{
public:
    WordRandomPlayer(string name, T symbol);
    void getmove(int &x, int &y);
};

void WordSetPlayerType(Player<char> *&player, int choice, string name, char symbol);
void WordInfo();
void WordTicTacToe();
vector<string> loadDictionary(string filename);
bool isValidWord(string word, const vector<string> &dic);

template <typename T>
WordBoard<T>::WordBoard()
{
    this->rows = 3;
    this->columns = 3;
    this->board = new T *[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++)
        {
            this->board[i][j] = T();
        }
    }
    this->n_moves = 0;

    dic = loadDictionary("dic.txt");
}

template <typename T>
WordBoard<T>::~WordBoard()
{
    for (int i = 0; i < this->rows; i++)
    {
        delete[] this->board[i];
    }
    delete[] this->board;
}

template <typename T>
bool WordBoard<T>::update_board(int x, int y, T symbol)
{
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != T())
    {
        if (wordIsRandom)
        {
            return false;
        }
        cout << "Invalid input please Enter the index of an Empty cell: " << endl;
        return false;
    }
    else
    {
        this->board[x][y] = symbol;
        this->n_moves++;
        return true;
    }
}

template <typename T>
void WordBoard<T>::display_board()
{
    cout << "\n   0   1   2" << endl;
    cout << "  +---+---+---+" << endl;
    for (int i = 0; i < this->rows; ++i)
    {
        cout << i << " |";
        for (int j = 0; j < this->columns; ++j)
        {
            cout << " " << this->board[i][j] << " |";
        }
        cout << "\n  +---+---+---+" << endl;
    }
}

template <typename T>
bool WordBoard<T>::is_win()
{
    for (int i = 0; i < this->rows; ++i)
    {
        string rowWord, colWord;
        for (int j = 0; j < this->columns; ++j)
        {
            rowWord += this->board[i][j];
            colWord += this->board[j][i];
        }
        if (isValidWord(rowWord, this->dic) || isValidWord(colWord, this->dic))
        {
            return true;
        }
    }

    string diag1, diag2;
    for (int i = 0; i < this->rows; ++i)
    {
        diag1 += this->board[i][i];
        diag2 += this->board[i][this->rows - i - 1];
    }
    if (isValidWord(diag1, this->dic) || isValidWord(diag2, this->dic))
    {
        return true;
    }
    return false;
}

template <typename T>
bool WordBoard<T>::is_draw()
{
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool WordBoard<T>::game_is_over()
{
    return is_win() || is_draw();
}

template <typename T>
WordPlayer<T>::WordPlayer(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void WordPlayer<T>::getmove(int &x, int &y)
{
    wordIsRandom = false;
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    cout << "\nPlease enter the letter: ";
    char letter;
    cin >> letter;
    this->symbol = toupper(letter);
}

// Constructor for X_O_Random_Player
template <typename T>
WordRandomPlayer<T>::WordRandomPlayer(string name, T symbol) : RandomPlayer<T>(symbol)
{
    wordIsRandom = true;
    this->dimension = 3;
    this->name = name;
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}

template <typename T>
void WordRandomPlayer<T>::getmove(int &x, int &y)
{
    x = (rand() % this->dimension); // Random number between 0 and 2
    y = (rand() % this->dimension); // Random number between 0 and 2

    this->symbol = (rand() % 26) + 'A'; // Random letter
}

#endif