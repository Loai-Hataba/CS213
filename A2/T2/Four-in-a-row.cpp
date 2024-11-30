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
    cout << "           ===== Welcome to Four-in-a-Row =====\n" << endl;
    cout << " A fun 2D twist to the classic Connect Four game.\n";
    cout << " Players mark the grid with Xs and Os, similar to Tic-Tac-Toe.\n\n";

    cout << " +----------------------------------------------------+\n";
    cout << " |                      Rules                         |\n";
    cout << " +----------------------------------------------------+\n";
    cout << " | The board consists of a 7x6 grid (7 columns, 6 rows). |\n";
    cout << " | Player 1 marks Xs; Player 2 marks Os.               |\n";
    cout << " | Players take turns marking the lowest available     |\n";
    cout << " | square in any column.                               |\n";
    cout << " +----------------------------------------------------+\n";

    cout << " +----------------------------------------------------+\n";
    cout << " |                     Winning                        |\n";
    cout << " +----------------------------------------------------+\n";
    cout << " | A player wins by forming four-in-a-row:            |\n";
    cout << " | - Horizontally                                      |\n";
    cout << " | - Vertically                                        |\n";
    cout << " | - Diagonally                                        |\n";
    cout << " | The game ends in a draw if the grid is filled and  |\n";
    cout << " | no player achieves four-in-a-row.                  |\n";
    cout << " +----------------------------------------------------+\n";

    cout << "\n                  Let the game begin!\n";
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
