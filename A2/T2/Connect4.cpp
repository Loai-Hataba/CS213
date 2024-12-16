#include "Connect4.h"
using namespace std;
void  Connect4SetPlayerType(Player<char>*& player, int choice, string name, char symbol) {
    switch (choice) {
        case 1:
            player = new Connect4_Human<char>(name, symbol);
            break;
        case 2:
            player = new Connect4_Random<char>(name, symbol);
            break;
        default:
            cout << "Invalid choice!" << endl;
            player = nullptr;
            break;
    }
}
void displayConnect4GameInfo() {
    cout << "======================= Welcome to Connect 4 Game  =========================\n";
    cout << "A 2D twist on the classic Connect Four game!\n\n";

    cout << "Rules:\n";
    cout << "  - The board is a 7x6 grid (7 columns, 6 rows).\n";
    cout << "  - Player 1 uses 'X'; Player 2 uses 'O'.\n";
    cout << "  - Players take turns marking the lowest available cell in a column.\n\n";

    cout << "Winning:\n";
    cout << "  - Form four-in-a-row:\n";
    cout << "    * Horizontally\n";
    cout << "    * Vertically\n";
    cout << "    * Diagonally\n";
    cout << "  - A draw occurs if the board is full with no winner.\n\n";
    cout << "===========================================================================\n\n";
    cin.ignore();
    cin.clear();

}

void Connect4 ( ) {
    Player<char>* players[2] ={nullptr, nullptr};
    auto* B = new Connect4_Board<char>();
    displayConnect4GameInfo();
    //// Set Player one
    string player1Name = getPlayerName(1) ;
    int choice = getPlayerType();
    Connect4SetPlayerType(players[0] , choice , player1Name, 'X');
    ////////////////////////////////////////////////
    //// Set Player two
    cin.ignore();
    string player2Name = getPlayerName(2) ;
    choice = getPlayerType();
    Connect4SetPlayerType(players[1] , choice , player2Name, 'O');
    ////////////////////////////////////////////////
    GameManager<char> connect4Game (B, players);
    connect4Game.run();
    for (auto & player : players) {
        delete player;
    }

}
