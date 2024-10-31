#include "Menu.h"

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
    if (choice == 0){

        while (true)
        {
            displayMenu();
            vector<string> Instructions = ExtractInst();
            Machine machine(Instructions); 
            machine.RunMachine(Instructions) ;
            while (true)
            {
                if (machine.IsHalt)
                {
                    char Ch = GetChoice("Would you like to reset the machine to its initial state? ", "Please choose an option:\n" 
                                        "  (Y) - Yes, reset the machine\n"
                                        "  (N) - No, continue with the current state", 'Y', 'N');
                    if (Ch == 'N')
                    {
                        std::cin.clear();                                                   // Clear any error state flags (e.g., from invalid input)
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Remove all characters up to and including the newline
                        vector<string> Instructions = ExtractInst();
                        machine.RunMachine(Instructions);
                    }
                    else if (Ch == 'Y')
                    {
                        cout << "The machine has been successfully reset and is ready for a fresh start!" << endl;
                        break;
                    }
                }
            }

            char Ch = GetChoice("Would you like to exit the program?", "Please choose an option:\n"
                                "  (Y) - Yes, exit the program\n"
                                "  (N) - No, continue using the program", 'Y', 'N');
            if (toupper(Ch) == 'N')
            {
                std::cin.clear();                                                   // Clear any error state flags (e.g., from invalid input)
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Remove all characters up to and including the newline
                continue;
            }
            else if (toupper(Ch) == 'Y')
            {
                cout << "Thank you for using Vole Machine! Have a great day, and goodbye!" << endl;
                break;
            }
            
        }
    }
    else if(choice == 1){
         // Displaying the header
    std::cout << CYAN << "---------------------------------------------------" << RESET << std::endl;
    std::cout << CYAN << "|" << BOLD << YELLOW << "                   Program Authors               " << RESET << CYAN << "|" << RESET << std::endl;
    std::cout << CYAN << "|-------------------------------------------------|" << RESET << std::endl;
    
    // Displaying each author's name and role
    std::cout << CYAN << "|" << RESET << " " << BOLD << GREEN << "Loai Hataba" << RESET << " - 20230553                          " << CYAN << "|" << RESET << std::endl;
    std::cout << CYAN << "|" << RESET << " " << BOLD << GREEN << "Abdullah Mohammed" << RESET << " - 20230231                    " << CYAN << "|" << RESET << std::endl;
    std::cout << CYAN << "|" << RESET << " " << BOLD << GREEN << "Hossam Abdelaziz" << RESET << " - 20230121                     " << CYAN << "|" << RESET << std::endl;

    // Displaying the footer
    std::cout << CYAN << "---------------------------------------------------" << RESET << std::endl;

    
    }
    else{
        cout << "Thank you for using Vole Machine! Goodbye!" << endl;
    }
    return 0;
}