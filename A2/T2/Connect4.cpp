#include <iostream>
#include "BoardGame_Classes.h"
#include "Four-in-a-row.h"

using namespace std;

int main() {
    int choice;
    Player<char>* players[2];
    auto* B = new Four_In_A_Row_Board<char>();
    string player1Name, player2Name;
    cout << "Welcome to FCAI Four-In-A-Row Game. :)\n";
    // Set up Player 1
    cout << "Enter Player 1 name: ";
    cin >> player1Name;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[0] = new Four_In_A_Row_Player<char>(player1Name, 'X');
            break;
        case 2:
            players[0] = new Four_In_A_Row_Random<char>(player1Name, 'X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            delete B;
            return 1;
    }

    // Set up Player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[1] = new Four_In_A_Row_Player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new Four_In_A_Row_Random<char>(player2Name, 'O');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            delete B;
            delete players[0]; // Clean up Player 1 if already allocated
            return 1;
    }

    // Main game loop
    int turn = 0; // Alternate turns between Player 1 and Player 2
    while (!B->game_is_over()) {
        B->display_board();
        cout << players[turn]->getname() << "'s turn (" << players[turn]->getsymbol() << "):\n";
        int column, row = 0;
        players[turn]->getmove(row, column);

        if (!B->update_board(row, column, players[turn]->getsymbol())) {
            cout << "Invalid move. Try again.\n";
            continue;
        }

        if (B->is_win()) {
            B->display_board();
            cout << players[turn]->getname() << " wins! Congratulations!\n";
            break;
        }

        if (B->is_draw()) {
            B->display_board();
            cout << "The game is a draw!\n";
            break;
        }

        // Switch to the other player
        turn = 1 - turn;
    }

    // Clean up
    delete B;
    for (auto & player : players) {
        delete player;
    }

    return 0;
}
