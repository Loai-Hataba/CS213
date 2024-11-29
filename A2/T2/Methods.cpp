//
// Created by abdal on 29/11/2024.
//

#include "Methods.h"

int getPlayerType() {
    int choice = 0;
    while (true) {
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cout << "3. AI Player\n";
        cout << "your choice ( 1 -> 3 ): ";
        cin >> choice;
        if(cin.fail()) {
            cin.clear();// Clear invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore rest of the line
            cout << "Invalid input please enter  an integer number: " <<endl;
        }
        else if (!(choice >=1  && choice <=3 )) {
            cout << "Invalid input please enter a number between 1 and 3 : " <<endl;
        }
        else {
            break;
        }
    }
    return choice ;
}

string getPlayerName(int PlayerNum) {
    string name = "" ;
    cout << "Enter Player "<< PlayerNum<< " name : "  ;
    getline(cin,name );
    return name;
}
