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
    string name;
    int pid;
    string sessionName;
    int memoryUsage;

    Process(string name, int pid, string sessionName, int memoryUsage)
        : name(move(name)), pid(pid), sessionName(move(sessionName)), memoryUsage(memoryUsage) {}
};

// Class to represent the list of running processes
class ProcessList
{
private:
    vector<Process> processes;
    void setList(vector<Process> p) { processes = p; }
    stringstream getCommandContent()
    {
        system("tasklist > processes.txt");
        ifstream file("processes.txt");
        stringstream pipe;
        if (file.is_open())
        {
            cout << "processes.txt opened Successfully !!\n";
            pipe << file.rdbuf();
            file.close();
            // remove("processes.txt");
        }
        else
        {
            cout << "there is an error in the file !!" << endl;
        }
        return pipe;
    }
    // Display the given processes
    void displayProcesses(const vector<Process> &processList) const
    {
        cout << left << setw(25) << "Image Name"
             << setw(10) << "PID"
             << setw(15) << "Session Name"
             << "Mem Usage (KB)" << endl;
        cout << string(64, '=') << endl;

        for (const auto &process : processList)
        {
            cout << left << setw(25) << process.name << setw(10) << process.pid << setw(15) << process.sessionName
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
        // Get the content of running "tasklist" so we can add every process to the list
        stringstream content = getCommandContent();
        vector<Process> fetched;
        string line = "";
        regex processRegex(R"(^\s*(.+?)\s+(\d+)\s+([\S ]+?)\s+([\d,]+) K\s*$)");
        // Skip the header lines
        while (getline(content, line))
        {
            if (line.find("Image Name") != string::npos)
            {
                break; // We found the header, stop reading
            }
        }

        // Now process each line (excluding the header)
        while (getline(content, line))
        {
            smatch match;
            if (regex_match(line, match, processRegex))
            {
                // cout << "yarab" << endl;
                string name = match[1].str();
                int pid = stoi(match[2].str());
                string sessionName = match[3].str();
                string memUsageStr = match[4].str();
                // cout << "yarab mem " << memUsageStr << endl;
                // cout << name << pid << sessionName << memUsageStr << endl;
                int memoryUsage = stoi(memUsageStr);

                // Create and add the process to the list
                fetched.emplace_back(name, pid, sessionName, memoryUsage);
            }
        }

        // Set the fetched processes into the private member
        setList(fetched);
    }

    void displaySortedByPID() const
    {
        vector<Process> sortedProcesses = processes;
        for (size_t i = 0; i < sortedProcesses.size(); ++i)
        {
            for (size_t j = 0; j < sortedProcesses.size() - i - 1; ++j)
            { // Fix the loop bounds
                if (sortedProcesses[j].pid > sortedProcesses[j + 1].pid)
                {
                    swap(sortedProcesses[j], sortedProcesses[j + 1]);
                }
            }
        }
        displayProcesses(sortedProcesses);
    }
    void displaySortedByMemory() const
    {
        vector<Process> sortedProcesses = processes;
        for (size_t i = 0; i < sortedProcesses.size(); ++i)
        {
            for (size_t j = 0; j < sortedProcesses.size() - i - 1; ++j)
            { // Fix the loop bounds
                if (sortedProcesses[j].memoryUsage > sortedProcesses[j + 1].memoryUsage)
                {
                    swap(sortedProcesses[j], sortedProcesses[j + 1]);
                }
            }
        }
        displayProcesses(sortedProcesses);
    }
    void displaySortedByName() const
    {
        vector<Process> sortedProcesses = processes;
        for (size_t i = 0; i < sortedProcesses.size(); ++i)
        {
            for (size_t j = 0; j < sortedProcesses.size() - i - 1; ++j)
            { // Fix the loop bounds
                if (sortedProcesses[j].name > sortedProcesses[j + 1].name)
                {
                    swap(sortedProcesses[j], sortedProcesses[j + 1]);
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
        string yarab = "    "; // 4
        cout << yarab.length() << endl;
        cout << "==== Welcome To Task Manager Simulator ====\n"
             << endl;
        cout << "Please choose which type of sorting you want : " << endl
             << "A) By name\n"
             << "B) By ID\n"
             << "C) By Memory Usage\n"
             << "D) Exit" << endl;
        string choice = "";
        cout << " Your Choice : ";
        cin >> choice;
        if (toupper(choice[0]) >= 'A' && toupper(choice[0]) <= 'D')
        {
            ProcessList TaskManger;
            TaskManger.fetchProcesses();
            switch (toupper(choice[0]))
            {
            case 'A':
                TaskManger.displaySortedByName();
                break;
            case 'B':
                TaskManger.displaySortedByPID();
                break;
            case 'C':
                TaskManger.displaySortedByMemory();
                break;
            case 'D':
                cout << "Exiting the program 0_0" << endl;
                return 0;
            default:
                cout << "It must There Is no Default :(" << endl;
                break;
            }
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Remove all characters up to and including the newline
            cout << "Invalid choice please enter a valid one 0_0 " << endl;
        }
    }

    return 0;
}
