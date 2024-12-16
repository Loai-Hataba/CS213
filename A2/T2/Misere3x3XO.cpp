#include "Misere3x3XO.h"
#include "methods.h"

void MisereSetPlayerType(Player<char> *&player, int choice, string name, char symbol)
{
    switch (choice)
    {
    case 1:
        player = new MiserePlayer<char>(name, symbol);
        break;
    case 2:
        player = new MisereRandomPlayer<char>(symbol);
        break;
    default:
        cout << "Invalid choice!" << endl;
        player = nullptr;
        break;
    }
}
void MisereGameInfo()
{
    cout << "\n======================= Welcome to Misere Tic Tac Toe Game ==================\n";
    cout << "A twist on the classic Tic-Tac-Toe where the goal is to avoid getting three marks in a row.\n\n";
    cout << "Rules:\n";
    cout << "  - Players take turns placing an X or an O in one of the squares.\n";
    cout << "  - The goal is to avoid forming three marks in a row, column, or diagonal.\n";
    cout << "  - The player who ends up with three marks in a row loses the game.\n";
    cout << "  - If all cells are filled without either player forming three marks in a row, the game ends in a draw.\n\n";
    cout << "Winning:\n";
    cout << "  - There is no winning condition. Instead, the player who places three marks in a row loses.\n";
    cout << "  - The game ends in a draw if no player forms a row of three marks and all cells are filled.\n";
    cout << "===========================================================================\n\n";

    cin.ignore();
    cin.clear();
}

void Misere()
{
    auto *B = new MisereBoard<char>();
    Player<char> *players[2] = {nullptr, nullptr};
    MisereGameInfo();
    //// Set Player one
    string player1Name = getPlayerName(1);
    int choice = getPlayerType();
    MisereSetPlayerType(players[0], choice, player1Name, 'X');
    //// Set Player two
    cin.ignore();
    string player2Name = getPlayerName(2);
    choice = getPlayerType();
    MisereSetPlayerType(players[1], choice, player2Name, 'O');
    GameManager<char> FourByFour_GameManger(B, players);
    FourByFour_GameManger.run();
    for (auto &player : players)
    {
        delete player;
    }
}