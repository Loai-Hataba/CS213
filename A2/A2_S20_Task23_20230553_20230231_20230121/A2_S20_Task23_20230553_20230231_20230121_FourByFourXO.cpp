//
// Created by abdallah on 03/12/2024.
//

#include "A2_S20_Task23_20230553_20230231_20230121_FourByFourXO.h"
void FourByFourSetPlayerType(Player<char> *&player, int choice, string name, char symbol)
{
    switch (choice)
    {
    case 1:
        player = new FourByFour_Player<char>(name, symbol);
        break;
    case 2:
        player = new FourByFour_Random<char>(name, symbol);
        break;
    default:
        cout << "Invalid choice!" << endl;
        player = nullptr;
        break;
    }
}
void TicTacToe4x4GameInfo()
{
    cout << "\n======================= Welcome to 4x4 Tic Tac Toe Game  ==================\n";
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
    cout << "===========================================================================\n\n";
    cin.ignore();
    cin.clear();
}

void TicTacToe4x4()
{
    auto *B = new FourByFour_Board<char>();
    Player<char> *players[2] = {nullptr, nullptr};
    TicTacToe4x4GameInfo();
    //// Set Player one
    string player1Name = getPlayerName(1);
    int choice = getPlayerType();
    FourByFourSetPlayerType(players[0], choice, player1Name, 'X');
    //// Set Player two
    cin.ignore();
    string player2Name = getPlayerName(2);
    choice = getPlayerType();
    FourByFourSetPlayerType(players[1], choice, player2Name, 'O');
    GameManager<char> FourByFour_GameManger(B, players);
    FourByFour_GameManger.run();
    for (auto &player : players)
    {
        delete player;
    }
}
