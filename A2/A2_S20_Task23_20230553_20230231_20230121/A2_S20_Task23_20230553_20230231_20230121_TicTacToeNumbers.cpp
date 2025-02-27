#include "A2_S20_Task23_20230553_20230231_20230121_TicTacToeNumbers.h"
#include <vector>
#include <algorithm>
int getPlayerSymbol(vector<int> &available)
{
    int playerSymbol = 0;
    while (true)
    {
        cout << endl
             << "Please Enter Your Symbol (Num)  between ( ";
        for (int i = 0; i < available.size(); i++)
        {
            if (i != available.size() - 1)
            {
                cout << available[i] << " , ";
            }
            else
            {
                cout << available[i];
            }
        }
        cout << " ) -->  ";
        cin >> playerSymbol;
        // the user input a non integer or any garbage
        if (cin.fail())
        {
            cin.clear();                                         // Clear invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore rest of the line
            cout << "Invalid input please enter  an integer number: " << endl;
        }
        else if (find(available.begin(), available.end(), playerSymbol) == available.end())
        {
            cout << playerSymbol << " is not a valid number." << endl;
        }
        else
        {
            auto it = find(available.begin(), available.end(), playerSymbol);
            if (it != available.end())
            {
                cout << "You have selected: " << playerSymbol << endl;
                break; // Exit the loop after successful selection
            }
            else
            {
                cout << playerSymbol << " is not a valid option. Please try again." << endl;
            }
        }
    }
    return playerSymbol;
}
void setPlayerType(Player<int> *&player, int choice, string name, int symbol)
{
    switch (choice)
    {
    case 1:
        player = new TicTacToeNum_Player<int>(name, symbol);
        break;
    case 2:
        player = new TicTacToeNum_Random<int>(name, symbol);
        break;
    default:
        cout << "Invalid choice!" << endl;
        player = nullptr;
        break;
    }
}

void NumericalTicTacToe()
{
    Player<int> *players[2] = {nullptr, nullptr};
    auto *B = new TicTacToeNum_Board<int>();
    displayNumTicTacToeInfo();
    ///// Symbol 0 --> even / symbol --> 1 --> odd numbers
    /////Setting Player 1
    string player1Name = getPlayerName(1);
    int choice = getPlayerType();
    setPlayerType(players[0], choice, player1Name, 1);
    /// Setting Player 2
    cin.ignore();
    string player2Name = getPlayerName(2);
    choice = getPlayerType();
    setPlayerType(players[1], choice, player2Name, 0);
    GameManager<int> NumTicTacToe(B, players);
    NumTicTacToe.run();
    for (auto &player : players)
    {
        delete player;
    }
}

void displayNumTicTacToeInfo()
{
    cout << "\n======================= Welcome to Numerical Tic Tac Toe ===========================\n\n";
    cout << "A mathematical twist on Tic-Tac-Toe! Players use numbers instead of \"X\" and \"O\".\n\n";
    cout << "Rules:\n";
    cout << "  - Player 1 uses odd numbers (1, 3, 5, 7, 9).\n";
    cout << "  - Player 2 uses even numbers (2, 4, 6, 8).\n";
    cout << "  - Objective: Achieve a sum of 15 in a row, column, or diagonal.\n";
    cout << "  - Numbers are placed in empty cells and can only be used once.\n";
    cout << "\nWinning:\n";
    cout << "  - Form a row, column, or diagonal with a sum of 15 to win.\n";
    cout << "  - If all cells are filled and no sum of 15 is achieved, it's a draw.\n";
    cout << "=====================================================================================\n\n";
    cin.ignore();
    cin.clear();
}
