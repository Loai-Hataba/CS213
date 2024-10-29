#include "Menu.h"
#include <regex>
#define GREEN "\e[32m"
#define RESET "\e[0m"
#define CYANBACK "\e[46m"
#define YELLOW "\e[33m"

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
cout << "      `\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"`    \'========\' " << endl;}
string GetFile()
{
    string Result;

    while (true)
    {
        string Path = GetPath();
        ifstream File(Path); // Open the file using ifstream
        if (File.fail())
        {
            // Check if the file failed to open
            cout << "Unable to open the file --> (" << Path << "). Please choose another one with (.txt) format." << endl;
        }
        else
        {
            cout << "The file --> (" << Path << ") opened successfully." << endl;

            // Read file content character by character
            char ch;
            while (File.get(ch)) // File.get() reads one character at a time
            {
                // Append only printable ASCII characters (from space to ~)
                if (ch >= 32 && ch <= 126)
                {
                    Result += ch;
                }
            }

            File.close(); // Close the file
            break;
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
        bool alpha = isdigit(Content[i]) || (Content[i] >= 'B' && Content[i] <= 'C');
        cout << Content[i] << endl;
        // If temp has 4 characters, push them as two separate hex pairs
        if (temp.size() == 4)
        {
            inst.push_back(temp.substr(0, 2));
            inst.push_back(temp.substr(2, 2));
            temp.clear();
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
            if(Content[i] == '7' ) continue;
            if(Content[i] == '8' ) continue;
            if(Content[i] == '9' ) continue;

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
    displayMenu();
    string Content  = GetFile () ;
    vector <string> Instructions  = ExtractInst (Content);
    Machine machine(Instructions);
    

    return 0 ;
}