#include "Headers.h"
#include "Machine.h"
#include <chrono>
#include <regex>
#include "options.h"


#define GREEN "\e[32m"
#define RESET "\e[0m"
#define CYANBACK "\e[46m"
#define CYAN    "\033[36m"
#define YELLOW "\e[33m"
#define BOLD    "\033[1m"



void displayMenu(){
cout << endl;
cout << "                            _______ " << endl;
cout << "                           | ___  o| " << endl;
cout << "                           |[_-_]_ | " << endl;
cout << "        ______________     |[_____]| " << endl;
cout << "       |.------------.|    |[_____]| " << endl;
cout << "       ||  "GREEN"Hello ya"RESET"  ||    |[====o]| " << endl;
cout << "       ||  "GREEN"User ya"RESET"   ||    |[_.--_]| " << endl;
cout << "       ||  "GREEN"Habibi to"RESET" ||    |[_____]| " << endl;
cout << "       ||"CYANBACK"Vole Machine"RESET"||    |      :| " << endl;
cout << "       ||____________||    |      :| " << endl;
cout << "   .==.|\"\"  ......    |.==.|      :| " << endl;
cout << "   |::| \'-.________.-\' |::||"YELLOW" CS213"RESET" | " << endl;
cout << "   |\'\'|  (__________)-.|\'\'||_______| " << endl;
cout << "   `\"\"`_.............._\\\"\"`______ " << endl;
cout << "      /:::::::::::\'\':::\\`;'-.-.  `\\ " << endl;
cout << "     /::=========.:.-::\"\\ \\ \\--\\   \\ " << endl;
cout << "     \\`\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"`/  \\ \\__)   \\ " << endl;
cout << "      `\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"`    \'========\' " << endl;
cout << endl << endl;
cout << "   What do you want to do today?\n\n";
}

int main()
{
    vector<string> options = {"Use Vole Machine", "Authors", "Exit"};
    int choice = navigateMenu(options);
    if (choice == 0)
    {
        while (true)
        {
            displayMenu();
            vector<string> Instructions = ExtractInst();
            Machine machine;
            machine .setInstructions(Instructions) ;
            machine.RunMachine();
            char Ch = GetChoice("Would you like to exit the program?", "Please choose an option:\n"
                                "  (Y) - Yes, exit the program\n"
                                "  (N) - No, continue using the program", 'Y', 'N');
            if (toupper(Ch) == 'N')
            {
                  cin.clear();                                                   // Clear any error state flags (e.g., from invalid input)
                  cin.ignore(  numeric_limits<  streamsize>::max(), '\n'); // Remove all characters up to and including the newline
                continue;
            }
            else if (toupper(Ch) == 'Y')
            {
                cout << "Thank you for using Vole Machine! Have a great day, and goodbye!" << endl;
                break;
            }
        }
    }
    else if (choice == 1)
    {
        // Displaying the header
          cout << CYAN << "---------------------------------------------------" << RESET <<   endl;
          cout << CYAN << "|" << BOLD << YELLOW << "                   Program Authors               " << RESET << CYAN << "|" << RESET <<   endl;
          cout << CYAN << "|-------------------------------------------------|" << RESET <<   endl;

        // Displaying each author's name and role
          cout << CYAN << "|" << RESET << " " << BOLD << GREEN << "Loai Hataba" << RESET << " - 20230553                          " << CYAN << "|" << RESET <<   endl;
          cout << CYAN << "|" << RESET << " " << BOLD << GREEN << "Abdullah Mohammed" << RESET << " - 20230231                    " << CYAN << "|" << RESET <<   endl;
          cout << CYAN << "|" << RESET << " " << BOLD << GREEN << "Hossam Abdelaziz" << RESET << " - 20230121                     " << CYAN << "|" << RESET <<   endl;

        // Displaying the footer
          cout << CYAN << "---------------------------------------------------" << RESET <<   endl;
    }
    else
    {
      cout << endl << "Thank you for using Vole Machine! Have a great day, and goodbye!" << endl;
    }
    return 0;
}