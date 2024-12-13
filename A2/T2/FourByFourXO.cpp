//
// Created by abdal on 03/12/2024.
//

#include "FourByFourXO.h"
void setType(Player<char>*& player, int choice, string name, char symbol) {
    switch (choice) {
        case 1:
            player = new FourByFourXO_Player<char>(name, symbol);
        break;
        case 2:
            player = new FourByFourXO_Random<char>(name, symbol);
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
void TicTacToe4x4GameInfo() {
    cout << "================== Welcome to 4x4 Tic-Tac-Toe ====================\n";
    cout << "An extended version of Tic-Tac-Toe with a 4x4 board.\n\n";

    cout << "Rules:\n";
    cout << "  - The board is a 4x4 grid.\n";
    cout << "  - Players start with four tokens in specific positions.\n";
    cout << "  - Tokens move to adjacent open squares (horizontally/vertically).\n";
    cout << "  - Tokens cannot jump over others or move diagonally.\n\n";

    cout << "Winning:\n";
    cout << "  - Align three tokens in a row:\n";
    cout << "    * Horizontally\n";
    cout << "    * Vertically\n";
    cout << "    * Diagonally\n";
    cout << "  - The game ends when a player achieves this goal.\n\n";

    cout << "=================================================================\n\n";

}

void TicTacToe4x4 () {
    auto * B = new FourByFourXO<char> ();
    Player<char>* players[2] ={nullptr, nullptr};
    TicTacToe4x4GameInfo() ;
    //// Set Player one
    string player1Name = getPlayerName(1) ;
    int choice = getPlayerType();
    setType(players[0] , choice , player1Name, 'X');
    ////////////////////////////////////////////////
    //// Set Player two
    cin.ignore();
    string player2Name = getPlayerName(2) ;
    choice = getPlayerType();
    setType(players[1] , choice , player2Name, 'O');
    ////////////////////////////////////////////////
    GameManager<char> connect4Game (B, players);
    connect4Game.run();
    for (auto & player : players) {
        delete player;
    }
}
