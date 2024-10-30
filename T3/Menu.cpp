#include "Menu.h"
#include <regex>
#include "options.h"

bool CheckInst(string Inst)
{
    if (!isdigit(Inst[0]) && (Inst[0] != 'B' || Inst[0] != 'C'))
        return false;

    return true;
}
#define GREEN "\e[32m"
#define RESET "\e[0m"
#define CYANBACK "\e[46m"
#define CYAN    "\033[36m"
#define YELLOW "\e[33m"
#define BOLD    "\033[1m"



void displayMenu(){
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
string GetFile()
{
    string Result;

    while (true)
    {
        string Path = GetPath();
        ifstream File(Path); // Open the file using ifstream
        if (File.is_open())
        { // Check if the file failed to open
            cout << "The File --> ( " << Path << " ) Opened Successfully " << endl; // Debugging line
            stringstream Content;
            Content << File.rdbuf(); // Read the entire file content
            Result = Content.str();  // Store the content in a string
            File.close();            // Close the file
            break;
        }
        else
        {                                                                           // File opened successfully
            cout << "Unable To Open The File --> ( " << Path << " ) . Please Choose Another One With (.txt) Format" << endl;
        }
    }
    return Result; // Return the file content
}
vector<string> ExtractInst(string Content)
{
    vector<string> inst;
    string temp;
    for (size_t i = 0; i < Content.size(); i++)
    {
        // Corrected the condition for alpha to ensure it checks both ranges properly
        bool alpha = isdigit(Content[i]) || (Content[i] >= 'A' && Content[i] <= 'F');
        cout << Content[i] << endl;
        // If temp has 4 characters, push them as two separate hex pairs
        if (temp.size() == 4)
        {
            if (CheckInst)
            {
                inst.push_back(temp.substr(0, 2));
                inst.push_back(temp.substr(2, 2));
                temp.clear();
            }
        }

        // If the character is a space and temp size is less than 4 or if the character is not valid, clear temp
        if ((isspace(Content[i]) && temp.size() < 4) || !alpha)
        {
            temp.clear(); // Invalid instruction
            continue;
        }

        // If the character is valid, add it to temp
        if (alpha)
        {
            temp += Content[i];
        }
    }

    // Ensure any remaining valid temp content is added
    if (!temp.empty() && temp.size() == 4)
    {
        inst.push_back(temp.substr(0, 2));
        inst.push_back(temp.substr(2, 2));
    }
    cout << endl;
    return inst;
}

int main()
{
    vector<string> options = {"Use Vole Machine", "Authors", "Exit"};
    int choice = navigateMenu(options);
    if (choice == 0){
        displayMenu();
        string Content  = GetFile () ;
        vector <string> Instructions  = ExtractInst (Content);
        Machine machine(Instructions);
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