#include "TicTacToeNumbers.h"
#include <Methods.h>
#include <vector>
#include <algorithm>
int getPlayerSymbol(vector<int> & available  ) {
    int playerSymbol = 0 ;
    while (true) {
        cout << endl << "Please Enter Your Symbol (Num)  between ( " ;
        for (int i = 0; i < available.size(); i++) {
           if(i != available.size() - 1) {
               cout << available[i] << " , ";
           }
            else {
                cout << available[i] ;
            }
        }
        cout << " ) -->  " ;
        cin >> playerSymbol;
        //the user input a non integer or any garbage
        if(cin.fail()) {
            cin.clear();// Clear invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore rest of the line
            cout << "Invalid input please enter  an integer number: " <<endl;
        }
        else if( find(available.begin(), available.end() , playerSymbol) == available.end()) {
            cout << playerSymbol << " is not a valid number." << endl;
        }
        else {
            auto it = find(available.begin() , available.end() , playerSymbol);
            if (it != available.end()) {
                available.erase(it); // Remove the selected symbol from available
                cout << "You have selected: " << playerSymbol << endl;
                break; // Exit the loop after successful selection
            }
            else {
                cout << playerSymbol << " is not a valid option. Please try again." << endl;
            }
        }
    }
    return playerSymbol  ;
}
void setPlayerType(Player<int>*& player, int choice, string name, int symbol) {
    switch (choice) {
        case 1:
            player = new TicTacToeNum_Player<int>(name, symbol);
        break;
        case 2:
            player = new TicTacToeNum_Random<int>(name, symbol);
        break;
        case 3:
            cout << "AI Player (not implemented)" << endl;
        player = nullptr; // Placeholder if AI is not implemented
        break;
        default:
            cout << "Invalid choice!" << endl;
        player = nullptr;
        break;
    }
}

void NumericalTicTacToe() {
    Player<int>* players[2] = {nullptr, nullptr};
    auto* B = new TicTacToeNum_Board<int>();
    displayNumTicTacToeInfo() ;
    ///////////////////////////////////////////////////////////////
    ///// Symbol 0 --> even / symbol --> 1 --> odd numbers
    /////Setting Player 1
    string player1Name = getPlayerName(1) ;
    int choice = getPlayerType();
    setPlayerType(players[0], choice, player1Name, 1);
    /////////////////////////////////////////////////////////////
    ///Setting Player 2
    cin.ignore();
    string player2Name = getPlayerName(2) ;
    choice = getPlayerType();
    setPlayerType(players[1], choice, player2Name, 0);
    ////////////////////////////////////////////////////////////////
    GameManager<int> NumTicTacToe (B, players);
    NumTicTacToe.run();
    for (auto & player : players) {
        delete player;
    }

}

void displayNumTicTacToeInfo() {
    cout << "           ===== Welcome to Numerical Tic Tac Toe =====\n" << endl;
    cout << " This game offers a mathematical twist to the classic Tic-Tac-Toe.\n";
    cout << " Instead of \"X\" and \"O\", players strategically use numbers.\n\n";

    cout << " +----------------------------------------------------+\n";
    cout << " |                      Rules                         |\n";
    cout << " +----------------------------------------------------+\n";
    cout << " | Player 1 uses odd numbers (1, 3, 5, 7, 9).         |\n";
    cout << " | Player 2 uses even numbers (2, 4, 6, 8).           |\n";
    cout << " | The objective is to achieve a sum of 15 in         |\n";
    cout << " | a row, column, or diagonal.                        |\n";
    cout << " | Players alternate turns, placing numbers in        |\n";
    cout << " | empty cells.                                       |\n";
    cout << " | Each number can only be used once.                 |\n";
    cout << " +----------------------------------------------------+\n";

    cout << " +----------------------------------------------------+\n";
    cout << " |                     Winning                        |\n";
    cout << " +----------------------------------------------------+\n";
    cout << " | A player wins by forming a row, column, or         |\n";
    cout << " | diagonal with a sum of 15.                         |\n";
    cout << " | If all cells are filled and no sum of 15 is        |\n";
    cout << " | achieved, the game ends in a draw.                 |\n";
    cout << " +----------------------------------------------------+\n";

    cout << "\n                  Let the game begin!\n";

}
