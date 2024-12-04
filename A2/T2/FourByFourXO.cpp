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
    cout << "           ===== Welcome to 4x4 Tic-Tac-Toe =====\n" << endl;
    cout << " An extended version of the classic Tic-Tac-Toe game\n";
    cout << " with more complex strategies and a 4x4 board.\n\n";

    cout << " +----------------------------------------------------+\n";
    cout << " |                      Rules                         |\n";
    cout << " +----------------------------------------------------+\n";
    cout << " | The board consists of a 4x4 grid.                  |\n";
    cout << " | Each player has four tokens, starting in specific  |\n";
    cout << " | positions.                                         |\n";
    cout << " | Players take turns moving one of their tokens to   |\n";
    cout << " | an adjacent open square (horizontally or vertically).|\n";
    cout << " | Tokens cannot jump over other tokens or move       |\n";
    cout << " | diagonally.                                        |\n";
    cout << " +----------------------------------------------------+\n";

    cout << " +----------------------------------------------------+\n";
    cout << " |                     Winning                        |\n";
    cout << " +----------------------------------------------------+\n";
    cout << " | A player wins by aligning three of their tokens in |\n";
    cout << " | a row:                                             |\n";
    cout << " | - Horizontally                                     |\n";
    cout << " | - Vertically                                       |\n";
    cout << " | - Diagonally                                       |\n";
    cout << " | The game ends when a player achieves this goal.    |\n";
    cout << " +----------------------------------------------------+\n";

    cout << "\n                  Let the game begin!\n";
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
    cout << "Yarab" <<endl;
    ////////////////////////////////////////////////
    GameManager<char> connect4Game (B, players);
    connect4Game.run();
    for (auto & player : players) {
        delete player;
    }
}
