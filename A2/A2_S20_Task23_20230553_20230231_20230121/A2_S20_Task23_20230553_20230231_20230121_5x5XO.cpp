#include "A2_S20_Task23_20230553_20230231_20230121_5x5XO.h"
#include "A2_S20_Task23_20230553_20230231_20230121_methods.h"

void XO5x5SetPlayerType(Player<char> *&player, int choice, string name, char symbol)
{
    switch (choice)
    {
    case 1:
        player = new XO_Player<char>(name, symbol);
        break;
    case 2:
        player = new XO_RandomPlayer<char>(symbol);
        break;
    default:
        cout << "Invalid choice!" << endl;
        player = nullptr;
        break;
    }
}
void XO5x5GameInfo()
{
    cout << "\n======================= Welcome to 5x5 Tic Tac Toe Game  ==================\n";
    cout << "A variation of Tic-Tac-Toe played on a 5x5 grid.\n\n";
    cout << "Rules:\n";
    cout << "  - Players take turns placing an X or an O in one of the squares.\n";
    cout << "  - The game ends when all squares except one are filled (each player has 12 turns).\n\n";
    cout << "Winning:\n";
    cout << "  - Count the number of three-in-a-row sequences (horizontal, vertical, or diagonal) for each player.\n";
    cout << "  - The player with the most three-in-a-row sequences wins.\n";
    cout << "  - Decide ahead of time whether a mark can be counted in more than one sequence.\n";
    cout << "===========================================================================\n\n";
    cin.ignore();
    cin.clear();
}

void XO5x5()
{

    auto *B = new XO_Board<char>();
    Player<char> *players[2] = {nullptr, nullptr};
    XO5x5GameInfo();
    //// Set Player one
    string player1Name = getPlayerName(1);
    int choice = getPlayerType();
    XO5x5SetPlayerType(players[0], choice, player1Name, 'X');
    //// Set Player two
    cin.ignore();
    string player2Name = getPlayerName(2);
    choice = getPlayerType();
    XO5x5SetPlayerType(players[1], choice, player2Name, 'O');
    GameManager<char> FourByFour_GameManger(B, players);
    FourByFour_GameManger.run();
    for (auto &player : players)
    {
        delete player;
    }
}
