#include "Methods.h"

int getPlayerType() {
    cout << endl << "What Is the Type Of Player?" << endl;
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    int choice = getValidIndex("Your choice (1 / 2): ", 1, 3);
    return choice;
}

string getPlayerName(int PlayerNum) {

    string name = "" ;
    cout << endl <<"Player "<< PlayerNum<< " name : "  ;
    getline(cin,name );
    return name;
}

/// Function to get a valid integer input
bool isInteger (string str) {
    for (const auto &ch : str) {
        if (!isdigit(ch)) {return false;}
    }
    return true ;
}
int getValidIndex(const string & message  , int start , int end  ) {
   while (true) {
       string str = "" ;
       int index = 0;
       cout << endl << message ;
       cin>> str ;
       if(isInteger(str)) {
           index = stoi(str);
           if (index >= start && index <= end) {
               return index;
           }
           else {
               cout << "Please enter an integer number between " << start << " and "  << end << " : ";
           }
       }
       else {
           cout << "You have entered an invalid input ,Please enter an integer number between " << start << " and "  << end << " : ";
       }
   }

}