#include "A2_S20_Task23_20230553_20230231_20230121_PyramicTicTacToe.h"
#include "A2_S20_Task23_20230553_20230231_20230121_Methods.h"

void PyramidSetPlayerType(Player<char> *&player, int choice, string name, char symbol)
{
    switch (choice)
    {
    case 1:
        player = new PyramidPlayer<char>(name, symbol);
        break;
    case 2:
        player = new PyramidRandomPlayer<char>(name, symbol);
        break;
    default:
        cout << "Invalid choice!" << endl;
        player = nullptr;
        break;
    }
}
void PyramidInfo()
{
    cout << "\n======================= Welcome to The Pyramid Tic Tac Toe Game  ==================\n";
    cout << "The game board is shaped like a pyramid. Five squares make the base, then three, then one.\n\n";
    cout << "Rules:\n";
    cout << "  - Players take turns marking Xs and Os as in traditional tic-tac-toe.\n\n";
    cout << "Winning:\n";
    cout << "  - The first player to get three-in-a-row vertically, horizontally, or diagonally wins.\n";
    cout << "===========================================================================\n\n";
    cin.ignore();
    cin.clear();
}

void PyramidTicTacToe()
{
    auto *B = new PyramidBoard<char>();
    Player<char> *players[2] = {nullptr, nullptr};
    PyramidInfo();
    //// Set Player one
    string player1Name = getPlayerName(1);
    int choice = getPlayerType();
    PyramidSetPlayerType(players[0], choice, player1Name, 'X');
    //// Set Player two
    cin.ignore();
    string player2Name = getPlayerName(2);
    choice = getPlayerType();
    PyramidSetPlayerType(players[1], choice, player2Name, 'O');
    GameManager<char> Pyramid_GameManger(B, players);
    Pyramid_GameManger.run();
    for (auto &player : players)
    {
        delete player;
    }
}

pair<int, int> makeIndex(int n)
{
    int cell = 1;
    map<int, pair<int, int>> index;
    index[cell++] = make_pair(0, 2);
    for (int i = 1; i < 4; ++i)
    {
        index[cell++] = make_pair(1, i);
    }
    for (int i = 0; i < 6; ++i)
    {
        index[cell++] = make_pair(2, i);
    }
    return index[n];
}
