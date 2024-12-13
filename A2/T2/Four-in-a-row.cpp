#include "Four-in-a-row.h"
#include "Methods.h"
using namespace std;
void setPlayerType(Player<char>*& player, int choice, string name, char symbol) {
    switch (choice) {
        case 1:
            player = new Four_In_A_Row_Player<char>(name, symbol);
            break;
        case 2:
            player = new Four_In_A_Row_Random<char>(name, symbol);
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
void displayConnect4GameInfo() {
    cout << "===== Welcome to Four-in-a-Row =====\n";
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

    cout << "Let the game begin!\n";
}

void Connect_Four_Game ( ) {
    Player<char>* players[2] ={nullptr, nullptr};
    auto* B = new Four_In_A_Row_Board<char>();
    displayConnect4GameInfo();
    //// Set Player one
    string player1Name = getPlayerName(1) ;
    int choice = getPlayerType();
    setPlayerType(players[0] , choice , player1Name, 'X');
    ////////////////////////////////////////////////
    //// Set Player two
    cin.ignore();
    string player2Name = getPlayerName(2) ;
    choice = getPlayerType();
    setPlayerType(players[1] , choice , player2Name, 'O');
    ////////////////////////////////////////////////
    GameManager<char> connect4Game (B, players);
    connect4Game.run();
    for (auto & player : players) {
        delete player;
    }

}
