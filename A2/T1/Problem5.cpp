#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include <limits>
using namespace std ;
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
    void setList(vector<Process> p){processes = p ;}
    string getCommandContent()
    {
        system("tasklist > processes.txt");
        ifstream file("processes.txt");
        string res = "";
        if (file.is_open())
        {
            cout << "processes.txt opened Successfully !!\n";
            stringstream pipe;
            pipe << file.rdbuf();
            res = pipe.str();
            file.close();
            remove("processes.txt");
        }
        else
        {
            cout << "there is an error in the file !!" <<endl;
        }
        return res ;
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
       // Get The Content of Running "tasklist" So we Can add Every Process to The list 
       string Content = getCommandContent() ;
       vector<Process> fetched ;
       string temp ;//
       for (size_t i = 0; i < Content.length(); i++)
       {

       }
        // Set The Fetched Processes Into The Private member 
        setList(fetched) ;
        return ;
    }

    // Display processes sorted by name
    void displaySortedByName() const
    {
        vector<Process> sortedProcesses = processes;

        // Bubble Sort to sort processes by name
        for (size_t i = 0; i < sortedProcesses.size(); ++i)
        {
            for (size_t j = 0; j < sortedProcesses.size() - i - 1; ++j)
            {
                if (sortedProcesses[j].name > sortedProcesses[j + 1].name)
                {
                    // Swap the elements if they are in the wrong order
                    swap(sortedProcesses[j], sortedProcesses[j + 1]);
                }
            }
        }

        displayProcesses(sortedProcesses);
    }

    // Display processes sorted by PID
    void displaySortedByPID() const
    {
        vector<Process> sortedProcesses = processes;
        for (size_t i = 0; i < sortedProcesses.size(); i++)
        {
            for (size_t j = 0; j < sortedProcesses.size(); j++)
            {
                if(sortedProcesses[j].pid>sortedProcesses[j+1].pid)
                {
                    swap(sortedProcesses[j],sortedProcesses[j+1]) ;
                }
            }
        }
        
        displayProcesses(sortedProcesses);
    }

    // Display processes sorted by memory usage
    void displaySortedByMemory() const
    {
        vector<Process> sortedProcesses = processes;
        for (size_t i = 0; i < sortedProcesses.size(); i++)
        {
            for (size_t j = 0; j < sortedProcesses.size(); j++)
            {
                if (sortedProcesses[j].memoryUsage > sortedProcesses[j + 1].memoryUsage)
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
      cout << "==== Welcome To Task Manager Simulator ====\n"<< endl;
      cout << "Please choose which type of sorting you want : " << endl
      << "A) By name\n" << "B) By ID\n"<<"C) By Memory Usage\n" <<endl; 
      string choice = "" ;
      cout << " Your Choice : "  ;
      cin>>choice;
      if(toupper(choice[0]) >='A' && toupper(choice[0]) <='C') 
      {
        ProcessList TaskManger ;
        TaskManger.fetchProcesses() ;
        switch (toupper(choice[0]))
        {
         case 'A':
            TaskManger.displaySortedByName() ;
            break;
         case 'B':
            TaskManger.displaySortedByPID() ;
            break;
         case 'C':
            TaskManger.displaySortedByMemory() ;
            break;
         default:
            cout << "It must There Is no Default :(" <<endl; 
            break;
        }
      }
      else 
      {
        cin.clear() ;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Remove all characters up to and including the newline
        cout << "Invalid choice please enter a valid one 0_0 "<<endl;
      }
  }
  
    return 0;
}
