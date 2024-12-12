// #ifndef _MISERE3X3XO_H
// #define _MISERE3X3XO_H
//
// #include "BoardGame_Classes.h"
//
// #define YELLOW "\033[33m"
// #define RESET "\033[0m"
// static bool turn = false; // starting turn X int->'0'
// static int lost = -1;     // starting at null players
// static bool won = false;
// static bool moves = true;
// static int temp_moves = 0;
//
// template <typename T>
// class MisereBoard : public Board<T>
// {
// public:
//     MisereBoard();
//     bool update_board(int x, int y, T symbol);
//     void display_board();
//     bool is_win();
//     bool is_draw();
//     bool game_is_over();
// };
//
// template <typename T>
// class MiserePlayer : public Player<T>
// {
// public:
//     MiserePlayer(string name, T symbol);
//     void getmove(int &x, int &y);
// };
//
// template <typename T>
// class MisereRandomPlayer : public RandomPlayer<T>
// {
// public:
//     MisereRandomPlayer(T symbol);
//     void getmove(int &x, int &y);
// };
//
// //--------------------------------------- IMPLEMENTATION
//
// #include <iostream>
// #include <iomanip>
// #include <cctype>
//
// using namespace std;
//
// template <typename T>
// MisereBoard<T>::MisereBoard()
// {
//     this->rows = this->columns = 3;
//     this->board = new char *[this->rows];
//     for (int i = 0; i < this->rows; i++)
//     {
//         this->board[i] = new char[this->columns];
//         for (int j = 0; j < this->columns; j++)
//         {
//             this->board[i][j] = 0;
//         }
//     }
//     this->n_moves = 0;
//     temp_moves = 0;
// }
//
// template <typename T>
// bool MisereBoard<T>::update_board(int x, int y, T mark)
// {
//     if (x == -1 && y == -1)
//     {
//         return true;
//     }
//     if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0))
//     {
//
//         if (mark == 0)
//         {
//             this->n_moves--;
//             temp_moves--;
//             this->board[x][y] = 0;
//         }
//         else
//         {
//             this->n_moves++;
//             temp_moves++;
//             this->board[x][y] = toupper(mark);
//         }
//
//         return true;
//     }
//     return false;
// }
//
// template <typename T>
// void MisereBoard<T>::display_board()
// {
//     cout << endl;
//     int width = 80;
//     int boardWidth = this->columns * 6 + 1;
//     int padding = (width - boardWidth) / 2;
//
//     for (int i = 0; i < this->rows; i++)
//     {
//         cout << string(padding, ' ') << "|";
//         for (int j = 0; j < this->columns; j++)
//         {
//             if (this->board[i][j] == 0) // Empty cell
//                 cout << "     |";
//             else
//                 cout << "  " << this->board[i][j] << "  |";
//         }
//         cout << "\n";
//         cout << string(padding, ' ');
//         for (int k = 0; k < this->columns; k++)
//             cout << "------";
//         cout << "-";
//         cout << endl;
//     }
//
//     cout << "\n~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.~.\n";
// }
//
// template <typename T>
// bool MisereBoard<T>::is_win()
// {
//     // cout << "Turn: " << turn << endl;
//
//     if (lost != -1)
//     {
//         if (turn != lost)
//         {
//             if (lost == 1)
//                 cout << "X wins\n";
//             if (lost == 0)
//             {
//                 return true;
//             }
//             won = true;
//             return false;
//         } // this player is the winner
//         else if (turn == lost)
//             return false; // this player is not the winner
//     }
//     for (int i = 0; i < this->rows; i++)
//     {
//         if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
//             (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0))
//         {
//             lost = turn; // indicates who lost X or O
//             // cout << "Turn row and columns : " << turn << endl;
//             turn = !turn;
//             moves = false;
//             return false;
//         }
//     }
//
//     // Check diagonals
//     if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
//         (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0))
//     {
//         lost = turn; // indicates who lost X or O
//         // cout << "Turning diagonal: " << turn << endl;
//         turn = !turn;
//         moves = false;
//         return false;
//     }
//
//     turn = !turn;
//     // cout << "finishing: " << turn << endl;
//     return false;
// }
//
// template <typename T>
// bool MisereBoard<T>::is_draw()
// {
//     return (this->n_moves == 9 && !is_win());
// }
//
// template <typename T>
// bool MisereBoard<T>::game_is_over()
// {
//     return (won || is_draw());
// }
//
// //--------------------------------------
//
// template <typename T>
// MiserePlayer<T>::MiserePlayer(string name, T symbol) : Player<T>(name, symbol) {}
//
// template <typename T>
// void MiserePlayer<T>::getmove(int &x, int &y)
// {
//     // cout << temp_moves << " \n";
//     if (temp_moves == 9 || !moves)
//     {
//         x = -1;
//         y = -1;
//         return;
//     }
//     cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
//     cin >> x >> y;
// }
//
// template <typename T>
// MisereRandomPlayer<T>::MisereRandomPlayer(T symbol) : RandomPlayer<T>(symbol)
// {
//     this->dimension = 3;
//     this->name = "Random Computer Player";
//     srand(static_cast<unsigned int>(time(0)));
// }
//
// template <typename T>
// void MisereRandomPlayer<T>::getmove(int &x, int &y)
// {
//     // cout << temp_moves << "  random\n";
//     if (temp_moves == 9 || !moves)
//     {
//         x = -1;
//         y = -1;
//         return;
//     }
//     x = rand() % this->dimension;
//     y = rand() % this->dimension;
// }
//
// #endif