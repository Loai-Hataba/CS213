#include "TicTacToeNumbers.h"
#include <Methods.h>
#include <vector>
#include <algorithm>
int getPlayerSymbol(vector<int> & available  ) {
    int playerSymbol = 0 ;
    while (true) {
        cout << "Please Enter Your Symbol (Num)  between ( " ;
        for(const auto & i : available) {
            cout << i << " ";
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
    vector<int> P1Nums ={1,3,5,7,9};
    vector<int> P2Nums ={2,4,6,8};
    cout << "Welcome to FCAI Tic Tac Toe With numbers. :)\n";
    ///////////////////////////////////////////////////////////////
    /////Setting Player 1
    string player1Name = getPlayerName(1) ;
    int choice = getPlayerType();
    int symbol =getPlayerSymbol(P1Nums);
    setPlayerType(players[0], choice, player1Name, symbol);
    /////////////////////////////////////////////////////////////
    ///Setting Player 2
    cin.ignore();
    string player2Name = getPlayerName(2) ;
    choice = getPlayerType();
    symbol =getPlayerSymbol(P2Nums);
    setPlayerType(players[1], choice, player2Name, symbol);
    ////////////////////////////////////////////////////////////////
    GameManager<int> NumTicTacToe (B, players);
    NumTicTacToe.run();
    for (auto & player : players) {
        delete player;
    }

}