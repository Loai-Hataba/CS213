// #ifndef ULTIMATETICTACTOE_H
// #define ULTIMATETICTACTOE_H
//
// #include <iostream>
// #include <iomanip>
// #include "BoardGame_Classes.h"
// #include "3x3X_O.h"
// #include "Methods.h"
//
// using namespace std;
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ///                        Small Board  Class
// template<class T>
// class SmallBoard : public  Board<T> {
// private:
//     void reset_board() ;
//     public:
//     SmallBoard();
//     ~SmallBoard();
//     bool update_board(int x, int y, T symbol);
//     void display_board();
//     bool is_win();
//     bool is_draw();
//     bool game_is_over();
// };
// /// Implementation
//
// template<class T>
// void SmallBoard<T>::reset_board() {
//     for (int i = 0; i < this->rows; ++i) {
//         for (int j = 0; j < this->columns; ++j) {
//             this->board[i][j] = T(); // Reset each cell to the default value of T
//         }
//     }
//     this->n_moves = 0; // Reset the move count
// }
//
// template<class T>
// SmallBoard<T>::SmallBoard() {
//     /// Build a grid of 3 x 3  to represent a normal X_O board
//     this->rows = 3 ;
//     this->columns = 3  ;
//     this->n_moves = 0 ;
//     this ->board = new T*[this -> rows];
//     for (int i = 0; i < this -> rows; i++) {
//         this -> board [i] = new T [this-> columns];
//         for (int j = 0; j < this-> columns; j++) {
//             this -> board[i][j] = T();
//         }
//     }
// }
//
// template<class T>
// SmallBoard<T>::~SmallBoard() {
//     for (int i = 0; i < this -> rows; i++) {
//         delete [] this->board[i];
//     }
//     delete [] this->board;
//     // Successfully deleting the stored memory
// }
//
// template<class T>
// bool SmallBoard<T>::update_board(int x, int y, T symbol) {
//     if(this->board[x][y] == T()) {
//         this->board[x][y] = symbol;
//         this->n_moves++;
//         return true;
//     }
//     return false;
// }
//
// template<class T>
// void SmallBoard<T>::display_board() {
//     for (int i = 0; i < this->rows; ++i) {
//         for (int j = 0; j < this->columns; ++j) {
//             cout << (this->board[i][j] == T() ? ' ' : this->board[i][j]);
//             if (j < this->columns - 1) cout << " | ";
//         }
//         cout << "\n";
//         if (i < this->rows - 1) cout << "---------\n";
//     }
// }
//
// template <class T>
// bool SmallBoard<T>::is_win() {
//     for (int i = 0; i < this->rows; ++i) {
//         if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != T()) ||
//             (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != T())) {
//             return true;
//             }
//     }
//     return (this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != T()) ||
//            (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != T());
// }
//
// template<class T>
// bool SmallBoard<T>::is_draw() {
//     if (this->n_moves == 9 && !is_win()) {
//         this -> reset_board();
//         return true;
//     }
//     return false;
// }
//
// template <class T>
// bool SmallBoard<T>::game_is_over() {
//     return is_win() || is_draw();
// }
//
//
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// template <typename T>
// class Ultimate_Board : public Board<T> {
// public:
//     // Constructor and Destructor
//     Ultimate_Board();
//     ~Ultimate_Board();
//
//     // Member functions
//     bool update_board(int x, int y, T symbol);
//     void display_board();
//     bool is_win();
//     bool is_draw();
//     bool game_is_over();
//
// private:
//     X_O_Board<T>** board;  // Override parent board with a 2D array of X_O_Board<T>
// };
// // PLayer Prototype
// template <typename T>
// class  UltimateTicTacToe_Player : public Player<T> {
//     public:
//     UltimateTicTacToe_Player(string name, T symbol);
//     void getmove(int &x, int &y);
// };
// ///// Game Prototype
// void setPlayerType(Player<char>*& player, int choice, string name, int symbol) ;
// void UltimateTicTacToe() ;
// void displayUltimateTicTacToeInfo() ;
// ////////////////////////////////////
// ///Random Player Prototype
// template <typename T>
// class UltimateTicTacToe_Random: public RandomPlayer<T> {
// public:
//     UltimateTicTacToe_Random(string name, T symbol);
//     void getmove(int &x, int &y);
// };
//
//
//
// /////////////////////////////////////////////////////////////////////////////////////////
// /// Board Implementation
// // Constructor
// template<typename T>
// Ultimate_Board<T>::Ultimate_Board() {
//     this->rows = this->columns = 3;
//     this->board = new X_O_Board<T>*[this->rows];
//     for (int i = 0; i < this->rows; i++) {
//         this->board[i] = new X_O_Board<T>[this->columns];  // Create 3x3 grid of X_O_Board<T>
//     }
//     this->n_moves = 0;
// }
//
// // Destructor
// template<typename T>
// Ultimate_Board<T>::~Ultimate_Board() {
//     for (int i = 0; i < this->rows; i++ ) {
//         delete[] this->board[i];
//     }
//     delete[] this->board;
// }
//
// // Display board
// template <typename T>
// void Ultimate_Board<T>::display_board() {
//     cout << "The Ultimate Grid : " <<endl;
//     for (int i = 0; i < this->rows; i++) {
//         cout << "\n| ";
//         for (int j = 0; j < this->columns; j++) {
//             cout << "(" << i << "," << j << ")";
//             cout << setw(2) << this-> board[i][j].get_symbol()  << " |";
//         }
//         cout << "\n-----------------------------";
//     }
//     cout << endl;
// }
//
//
// // Update board (placeholder implementation)
// template<typename T>
// bool Ultimate_Board<T>::update_board(int x, int y, T symbol)
// {
//     if(this->board[x][y].is_win()) {
//         this->n_moves++;
//         return true;
//     }
//     return false;
// }
//
// template<typename T>
// bool Ultimate_Board<T>::is_win() {
//     cout << "Check for win" << endl;
//
//     // For vertical win
//     for (int i = 0; i < this->columns; i++) {
//         if (this->board[i][0].get_symbol() == this->board[i][1].get_symbol() &&
//             this->board[i][1].get_symbol() == this->board[i][2].get_symbol() &&
//             this->board[i][0].get_symbol() != T()) {
//             return true;
//             }
//     }
//
//     // For horizontal win
//     for (int i = 0; i < this->columns; i++) {
//         if (this->board[0][i].get_symbol() == this->board[1][i].get_symbol() &&
//             this->board[1][i].get_symbol() == this->board[2][i].get_symbol() &&
//             this->board[0][i].get_symbol() != T()) {
//             return true;
//             }
//     }
//
//     // For diagonal win
//     if (this->board[0][0].get_symbol() == this->board[1][1].get_symbol() &&
//         this->board[1][1].get_symbol() == this->board[2][2].get_symbol() &&
//         this->board[0][0].get_symbol() != T()) {
//         return true;
//         }
//
//     if (this->board[0][2].get_symbol() == this->board[1][1].get_symbol() &&
//         this->board[1][1].get_symbol() == this->board[2][0].get_symbol() &&
//         this->board[0][2].get_symbol() != T()) {
//         return true;
//         }
//
//     // No win found
//     return false;
// }
//
//
// // Check draw
// template<typename T> // Done
// bool Ultimate_Board<T>::is_draw() {
//     return (this->n_moves == 9 && !is_win());
// }
//
// // Check if game is over
// template<typename T> // Done
// bool Ultimate_Board<T>::game_is_over() {
//     return is_win() || is_draw();
// }
//
//
//
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //// Player Implementation
// template<typename T>
// UltimateTicTacToe_Player<T>::UltimateTicTacToe_Player(string name, T symbol) : Player<T> (name ,symbol) {}
//
// template<typename T>
// void UltimateTicTacToe_Player<T>::getmove(int &x, int &y) {
//     cout << " ( "<<this -> getname() <<" ) Please enter which cell do you want :  " <<endl;
//     x =  getValidIndex( "the x index : " , 0 , 2 );
//     y =  getValidIndex( "the y index : " , 0 , 2 );
// }
//
//
//
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ///Random Player Implementation
// template<typename T>
// UltimateTicTacToe_Random<T>::UltimateTicTacToe_Random(string name, T symbol) : RandomPlayer<T>(symbol) {
//     this->dimension = 3;
//     this->name = name ;
//     srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
// }
//
// template<typename T>
// void UltimateTicTacToe_Random<T>::getmove(int &x, int &y) {
//     while (true) {
//         x = rand() % this->dimension ; // Random number between 0 and 2
//         if((x >= 0 && x <=2 )) {
//             break;
//         }
//     }
//     while (true) {
//         y = rand() % this->dimension ; // Random number between 0 and 2
//         if((y >= 0 && y <=2 )) {
//             break;
//         }
//     }
// }
//
// #endif // ULTIMATETICTACTOE_H
