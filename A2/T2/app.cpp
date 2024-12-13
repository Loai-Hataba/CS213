#include <iostream>
#include "BoardGame_Classes.h"
#include "3x3X_O.h"
#include "5x5XO.h"
#include "Misere3x3XO.h"
#include "MinMaxPlayer.h"
#include "Connect4.h"
#include "TicTacToeNumbers.h"
#include "UltimateTicTacToe.h"
#include "ultimateXO.h"
#include "FourByFourXO.h"

// Menu info
void DisplayMenuInfo();
using namespace std;
//              Original main
// int main()
// {
//     int choice;
//     Player<char> *players[2];
//     X_O_Board<char> *B = new X_O_Board<char>();
//     string playerXName, player2Name;
//     cout << "Welcome to FCAI X-O Game. :)\n";

//     // Set up player 1
//     cout << "Enter Player X name: ";
//     cin >> playerXName;
//     cout << "Choose Player X type:\n";
//     cout << "1. Human\n";
//     cout << "2. Random Computer\n";
//     cout << "3. Smart Computer (AI)\n";
//     cin >> choice;

//     switch (choice)
//     {
//     case 1:
//         players[0] = new X_O_Player<char>(playerXName, 'X');
//         break;
//     case 2:
//         players[0] = new X_O_Random_Player<char>('X');
//         break;
//     case 3:
//         players[0] = new X_O_MinMax_Player<char>('X');
//         players[0]->setBoard(B);
//         break;
//     default:
//         cout << "Invalid choice for Player 1. Exiting the game.\n";
//         return 1;
//     }

//     // Set up player 2
//     cout << "Enter Player 2 name: ";
//     cin >> player2Name;
//     cout << "Choose Player 2 type:\n";
//     cout << "1. Human\n";
//     cout << "2. Random Computer\n";
//     cout << "3. Smart Computer (AI)\n";
//     cin >> choice;

//     switch (choice)
//     {
//     case 1:
//         players[1] = new X_O_Player<char>(player2Name, 'O');
//         break;
//     case 2:
//         players[1] = new X_O_Random_Player<char>('O');
//         break;
//     case 3:
//         players[1] = new X_O_MinMax_Player<char>('O');
//         players[1]->setBoard(B);
//         break;
//     default:
//         cout << "Invalid choice for Player 2. Exiting the game.\n";
//         return 1;
//     }

//     // Create the game manager and run the game
//     GameManager<char> x_o_game(B, players);
//     x_o_game.run();

//     // Clean up
//     delete B;
//     for (int i = 0; i < 2; ++i)
//     {
//         delete players[i];
//     }

//     return 0;
// }
////////////////////////// Loai
// int choice;
// Player<char> *players[2];
// UltimateBoard<char> *B = new UltimateBoard<char>();
// string playerXName, player2Name;
// cout << "Welcome to FCAI  X-O Game. :)\n";
//
// // Set up player 1
// cout << "Enter Player X name: ";
// cin >> playerXName;
// cout << "Choose Player X type:\n";
// cout << "1. Human\n";
// cout << "2. Random Computer\n";
// cout << "3. Smart Computer (AI)\n";
// cin >> choice;
//
// switch (choice)
// {
// case 1:
//     players[0] = new UltimatePlayer<char>(playerXName, 'X');
//     break;
// case 2:
//     players[0] = new UltimateRandomPlayer<char>('X');
//     break;
// case 3:
//     players[0] = new X_O_MinMax_Player<char>('X');
//     players[0]->setBoard(B);
//     break;
// default:
//     cout << "Invalid choice for Player 1. Exiting the game.\n";
//     return 1;
// }
//
// // Set up player 2
// cout << "Enter Player 2 name: ";
// cin >> player2Name;
// cout << "Choose Player 2 type:\n";
// cout << "1. Human\n";
// cout << "2. Random Computer\n";
// cout << "3. Smart Computer (AI)\n";
// cin >> choice;
//
// switch (choice)
// {
// case 1:
//     players[1] = new UltimatePlayer<char>(player2Name, 'O');
//     break;
// case 2:
//     players[1] = new UltimateRandomPlayer<char>('O');
//     break;
// case 3:
//     players[1] = new X_O_MinMax_Player<char>('O');
//     players[1]->setBoard(B);
//     break;
// default:
//     cout << "Invalid choice for Player 2. Exiting the game.\n";
//     return 1;
// }
//
// // Create the game manager and run the game
// GameManager<char> ultimate(B, players);
// ultimate.run();
//
// // Clean up
// delete B;
// for (int i = 0; i < 2; ++i)
// {
//     delete players[i];
// }
int main()
{
    int Choice = 0;
    DisplayMenuInfo();
    while (true)
    {
        Choice = getValidIndex("Enter the Number Of Game You want : ", 1, 9);
        switch (Choice)
        {
        case 1:
            cout << "Pyramic Game " << endl;
            break;
        case 2:
            Connect4();
            break;
        case 3:
            XO5x5();
            break;
        case 4:
            cout << " Word Tic Tac Toe " << endl;
            break;
        case 5:
            NumericalTicTacToe();
            break;
        case 6:
            cout << " Misere Tic Tac Toe" << endl;
            break;
        case 7:
            TicTacToe4x4();
            break;
        case 8:
            UltimateXO();
            break;
        case 9:
            cout << "Terminating The Program" << endl;
            return 0;
        default:
            break;
        }
    }
}
void DisplayMenuInfo()
{
    cout << "\n================== Welcome to FCAI Board Games ==========================\n";
    cout << "   This application is brought to you as part of the CS213 course.\n";
    cout << "   Developed by :\n\tAbdallah Mohamed Abdallah\n\tHossam Mohamed Ahmed\n\tLoai Walid Hataba\n";
    cout << "\n Under the supervision of Dr. Mohammed El-Ramly\n";
    cout << "   Explore and enjoy 8 exciting board games designed for fun and strategy!\n";
    cout << "\n   Available Games:\n";
    cout << "   1) Pyramid Tic Tac Toe               2) Connect 4\n";
    cout << "   3) 5x5 Tic Tac Toe                   4) Word Tic Tac Toe\n";
    cout << "   5) Numerical Tic Tac Toe             6) Misere Tic Tac Toe\n";
    cout << "   7) 4x4 Tic Tac Toe                   8) Ultimate Tic Tac Toe\n";
    cout << "\n   We hope you enjoy the games. Have fun playing!\n";
    cout << "===========================================================================\n\n";
}
