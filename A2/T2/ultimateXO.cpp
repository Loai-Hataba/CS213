#include "ultimateXO.h"

void UltimateXOSetPlayerType(Player<char> *&player, int choice, string name, char symbol)
{
    switch (choice)
    {
    case 1:
        player = new UltimatePlayer<char>(name, symbol);
        break;
    case 2:
        player = new UltimateRandomPlayer<char>(symbol);
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
void UltimateXOGameInfo()
{
    cout << "======================= Welcome to Ultimate Tic Tac Toe Game  ==================\n";
    cout << "An expanded version of Tic-Tac-Toe with a 3x3 grid of smaller boards.\n\n";
    cout << "Rules:\n";
    cout << "  - The main board is a 3x3 grid, each cell containing a smaller 3x3 Tic Tac Toe board.\n";
    cout << "  - Player 1 starts by choosing any of the nine smaller boards to play on.\n";
    cout << "  - Players alternate turns, playing Tic Tac Toe on the smaller boards.\n";
    cout << "  - The winner of each smaller board places their symbol (X or O) on the main board.\n\n";
    cout << "Winning:\n";
    cout << "  - The first player to win three smaller boards in a row (horizontal, vertical, or diagonal) on the main board wins the game.\n";
    cout << "===========================================================================\n\n";
    cin.ignore();
    cin.clear();
}

void UltimateXO()
{
    auto *B = new UltimateBoard<char>();
    Player<char> *players[2] = {nullptr, nullptr};
    UltimateXOGameInfo();
    //// Set Player one
    string player1Name = getPlayerName(1);
    int choice = getPlayerType();
    UltimateXOSetPlayerType(players[0], choice, player1Name, 'X');
    //// Set Player two
    cin.ignore();
    string player2Name = getPlayerName(2);
    choice = getPlayerType();
    UltimateXOSetPlayerType(players[1], choice, player2Name, 'O');
    GameManager<char> ultimate_GameManger(B, players);
    ultimate_GameManger.run();
    for (auto &player : players)
    {
        delete player;
    }
}
