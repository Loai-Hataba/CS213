#include "A2_S20_Task23_20230553_20230231_20230121_5x5XO.h"
#include "A2_S20_Task23_20230553_20230231_20230121_Misere3x3XO.h"
#include "A2_S20_Task23_20230553_20230231_20230121_Connect4.h"
#include "A2_S20_Task23_20230553_20230231_20230121_TicTacToeNumbers.h"
#include "A2_S20_Task23_20230553_20230231_20230121_ultimateXO.h"
#include "A2_S20_Task23_20230553_20230231_20230121_FourByFourXO.h"
#include "A2_S20_Task23_20230553_20230231_20230121_PyramicTicTacToe.h"
#include "A2_S20_Task23_20230553_20230231_20230121_WordTicTacToe.h"

// Menu info
void DisplayMenuInfo();
void DisplayGamesNumber();
using namespace std;
int main()
{
    DisplayMenuInfo();
    while (true)
    {
        DisplayGamesNumber();
        int Choice = getValidIndex("Enter Your Choice  : ", 1, 9);
        switch (Choice)
        {
        case 1:
            PyramidTicTacToe();
            break;
        case 2:
            Connect4();
            break;
        case 3:
            XO5x5();
            break;
        case 4:
            WordTicTacToe();
            break;
        case 5:
            NumericalTicTacToe();
            break;
        case 6:
            Misere();
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
    cout << "\n   We hope you enjoy the games. Have fun playing!\n";
    cout << "===========================================================================\n";
}
void DisplayGamesNumber()
{
    cout << "\n   Available Games:\n";
    cout << "   1) Pyramid Tic Tac Toe               2) Connect 4\n";
    cout << "   3) 5x5 Tic Tac Toe                   4) Word Tic Tac Toe\n";
    cout << "   5) Numerical Tic Tac Toe             6) Misere Tic Tac Toe\n";
    cout << "   7) 4x4 Tic Tac Toe                   8) Ultimate Tic Tac Toe\n";
    cout << "   9) Exit :(" << endl;
}