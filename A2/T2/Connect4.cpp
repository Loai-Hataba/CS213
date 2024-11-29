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
    while (true) {
        // Set up Player 1
        cout << "Enter Player 1 name: ";
        getline(cin, player1Name );
        cout << "Choose Player 1 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;
        if(cin.fail()) {
            cin.clear();// Clear invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore rest of the line
            cout << "Invalid input please enter  an integer number: " <<endl;
        }
        else if (!(choice >=1  && choice <=2 )) {
            cout << "Invalid input please enter a number between 1 and 2 : " <<endl;
        }
        else {
            break;
        }
    }
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

    while (true) {
        // Set up Player 2
        cout << "Enter Player 2 name: ";
        getline(cin, player2Name ) ;
        cout << "Choose Player 2 type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;
        if(cin.fail()) {
            cin.clear();// Clear invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore rest of the line
            cout << "Invalid input please enter  an integer number: " <<endl;
        }
        else if (!(choice >=1  && choice <=2 )) {
            cout << "Invalid input please enter a number between 1 and 2 : " <<endl;
        }
        else {
            break;
        }
    }

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
    GameManager<char> x_o_game(B, players);
    x_o_game.run();
    // Clean up
    delete B;
    for (auto & player : players) {
        delete player;
    }

    return 0;
}
