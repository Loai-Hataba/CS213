#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include <regex>
#include <limits>
using namespace std;

// Class to represent a process
class Process
{
public:
    string name;        // Name of the process
    int pid;            // Process ID
    string sessionName; // Name of the session associated with the process
    long memoryUsage;   // Memory usage of the process in KB
    int sessionNumber;  // Session number associated with the process

    // Parametrized constructor
    Process(string n, int i, string sName, int sNum, long mu)
    {
        name = n;             
        pid = i;              
        sessionName = sName;  
        sessionNumber = sNum; 
        memoryUsage = mu;     
    }
};

// Class to represent the list of running processes
class ProcessList
{
private:
    vector<Process> processes; // Vector to store all processes

    // Set the list of processes
    void setList(vector<Process> p) { processes = p; }

    // Get the content of "tasklist" command output via a file
    stringstream getCommandContent()
    {
        // Run "tasklist" command and save output to a file
        system("tasklist > processes.txt");
        ifstream file("processes.txt"); // Open the file
        stringstream pipe;              // String stream to hold file content
        if (file.is_open())
        {
            pipe << file.rdbuf();    // Read the file content into the stream
            file.close();            // Close the file
            remove("processes.txt"); // Delete the file
        }
        else
        {
            cout << "there is an error in the file !!" << endl;
        }
        return pipe;
    }

    // Display the given processes in a formatted way
    void displayProcesses(const vector<Process> &processList) const
    {
        // Print the header row
        cout << left << setw(25) << "Image Name"
             << setw(10) << "PID"
             << setw(17) << "Session Name"
             << setw(15) << "Session #"
             << "Mem Usage (KB)" << endl;
        cout << string(80, '=') << endl;

        // Print each process in the list
        for (const auto &process : processList)
        {
            cout << left << setw(25) << process.name.substr(0, 25)
                 << setw(10) << process.pid
                 << setw(20) << process.sessionName
                 << setw(15) << process.sessionNumber
                 << process.memoryUsage << endl;
        }
    }

public:
    // Add a process to the list
    void addProcess(const Process &process)
    {
        processes.push_back(process);
    }

    // Fetch processes using system("tasklist") and populate the list
    void fetchProcesses()
    {
        // Get the content of the "tasklist" command
        stringstream content = getCommandContent();
        vector<Process> fetched;                                                               // Temporary vector to store fetched processes
        string line = "";                                                                      // Variable to hold each line of the content
        regex processRegex(R"(^\s*(.+\.exe)\s+(\d+)\s+([\S ]+?)\s+(\d+)\s+([\d,]+)\s*K\s*$)"); // Regex pattern to match processes

        // Skip the header lines
        while (getline(content, line))
        {
            if (line.find("Image Name") != string::npos)
            {
                break; // Stop reading when the header is found
            }
        }

        // Process each line (excluding the header)
        while (getline(content, line))
        {
            smatch match;
            // Match each line with the regex pattern
            if (regex_match(line, match, processRegex))
            {
                string name = match[1].str();          // Extract process name
                int pid = stoi(match[2].str());        // Extract process ID
                string sessionName = match[3].str();   // Extract session name
                int sessionNum = stoi(match[4].str()); // Extract session number
                string memUsageStr = match[5].str();   // Extract memory usage
                // Remove commas from memory usage
                memUsageStr.erase(remove(memUsageStr.begin(), memUsageStr.end(), ','), memUsageStr.end());
                // Convert memory usage to long
                long memoryUsage = stoll(memUsageStr);
                // Create a Process object and add it to the list
                Process process(name, pid, sessionName, sessionNum, memoryUsage);
                fetched.push_back(process);
            }
        }

        // Set the fetched processes into the private member
        setList(fetched);
    }

    // Display processes sorted by PID (ascending order)
    void displaySortedByPID() 
    {
        vector<Process> sortedProcesses = processes; 
        for (size_t i = 0; i < sortedProcesses.size(); ++i)
        {
            for (size_t j = 0; j < sortedProcesses.size() - i - 1; ++j)
            { // Bubble sort implementation
                if (sortedProcesses[j].pid > sortedProcesses[j + 1].pid)
                {
                    swap(sortedProcesses[j], sortedProcesses[j + 1]); // Swap elements if out of order
                }
            }
        }
        displayProcesses(sortedProcesses); // Display the sorted processes
    }

    // Display processes sorted by memory usage (ascending order)
    void displaySortedByMemory() 
    {
        vector<Process> sortedProcesses = processes;
        for (size_t i = 0; i < sortedProcesses.size(); ++i)
        {
            for (size_t j = 0; j < sortedProcesses.size() - i - 1; ++j)
            { // Bubble sort implementation
                if (sortedProcesses[j].memoryUsage > sortedProcesses[j + 1].memoryUsage)
                {
                    swap(sortedProcesses[j], sortedProcesses[j + 1]); // Swap elements if out of order
                }
            }
        }
        displayProcesses(sortedProcesses); 
    }

    // Display processes sorted by name (alphabetical order)
    void displaySortedByName() 
    {
        vector<Process> sortedProcesses = processes; 
        for (size_t i = 0; i < sortedProcesses.size(); ++i)
        {
            for (size_t j = 0; j < sortedProcesses.size() - i - 1; ++j)
            { // Bubble sort implementation
                if (sortedProcesses[j].name[0] > sortedProcesses[j + 1].name[0])
                {
                    swap(sortedProcesses[j], sortedProcesses[j + 1]); // Swap elements if out of order
                }
            }
        }
        displayProcesses(sortedProcesses); 
    }
};

// Main function to test the classes
int main()
{
    while (true)
    {
        // Display menu options
        cout << "==== Welcome To Task Manager Simulator ====\n"<< endl;
        cout << "Please choose which type of sorting you want : " << endl
             << "A) By name\n"
             << "B) By ID\n"
             << "C) By Memory Usage\n"
             << "D) Exit" << endl;

        string choice = ""; 
        cout << " Your Choice : ";
        cin >> choice;
        if(choice.size() > 1)
        {
            cin.clear();                                         // Clear invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore rest of the line
            cout << "Too long choice please make sure it (A->D) / (a->d) " << endl;
            continue; 
        }
        if (toupper(choice[0]) >= 'A' && toupper(choice[0]) <= 'D')
        {
            ProcessList TaskManger;      // Create an instance of ProcessList
            TaskManger.fetchProcesses(); // Fetch the processes
            switch (toupper(choice[0]))
            {
            case 'A':
                TaskManger.displaySortedByName(); // Display processes sorted by name
                break;
            case 'B':
                TaskManger.displaySortedByPID(); // Display processes sorted by PID
                break;
            case 'C':
                TaskManger.displaySortedByMemory(); // Display processes sorted by memory usage
                break;
            case 'D':
                cout << "Exiting the program 0_0" << endl;
                return 0; // Exit the program
            default:
                cout << "It must There Is no Default :(" << endl;
                break;
            }
        }
        else
        {
            cin.clear();                                         // Clear invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore rest of the line
            cout << "Invalid choice please enter a valid one 0_0 " << endl;
        }
    }

    return 0; 
}
