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

void Connect_Four_Game ( ) {
    Player<char>* players[2] ={nullptr, nullptr};
    auto* B = new Four_In_A_Row_Board<char>();
    cout << "Welcome to FCAI Connect 4 Game. :)\n";
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
    // Main game loop
    int turn = 0; // Alternate turns between Player 1 and Player 2
    GameManager<char> connect4Game (B, players);
    connect4Game.run();
    for (auto & player : players) {
        delete player;
    }

}
