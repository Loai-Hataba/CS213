#include "Instructions.h"
 int FileNum = 0;   
string GetPath()
{
   string Res;
    cout << "\nPlease Enter The Path Like This Formula --- >  C:\\Users\\YourUsername\\Documents\\example.txt" << endl;
    cout << "Please Enter The Path Of The File Number " << FileNum << ": ";
    // Clear the input buffer entirely before taking input
    if(FileNum == 1 ) cin.ignore(1, '\n');
    else cin.ignore(0, '\n');
    // Use getline to capture the entire file path, including spaces and special characters
    getline(cin, Res);
    return Res;
}
string GetContent()
{
    string Result;

    while (true)
    {
        string Path = GetPath();
        ifstream File(Path); // Open the file using ifstream
        if (File.fail())
        { // Check if the file failed to open
            cout << "Unable To Open The File --> ( " << Path << " ) . Please Choose Another One With (.txt) Format" << endl;
        }
        else
        {                                                                           // File opened successfully
            cout << "The File --> ( " << Path << " ) Opened Successfully " << endl; // Debugging line
            stringstream Content;
            Content << File.rdbuf(); // Read the entire file content
            Result = Content.str();  // Store the content in a string
            File.close();            // Close the file
            FileNum++;
            break;
        }
    }
    return Result; // Return the file content
}
vector<string> Extract(string Content)
{
    vector<string> inst;
    string temp;
    for (size_t i = 0; i < Content.size(); i++)
    {
        // Corrected the condition for alpha to ensure it checks both ranges properly
        bool alpha = isdigit(Content[i]) || (Content[i] >= 'A' && Content[i] <= 'F');

        // If temp has 4 characters, push them as two separate hex pairs
        if (temp.size() == 4)
        {
            inst.push_back(temp.substr(0, 2));
            inst.push_back(temp.substr(2, 2));
            temp.clear();
            cout << "done " << endl;
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

    return inst;
}
