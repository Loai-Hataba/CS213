#ifndef MACHINE_H
#define MACHINE_H // Include guard to prevent multiple inclusions of this header file

#include "CPU.h"      // Includes the CPU class definition
#include "Memory.h"    // Includes the Memory class definition
#include "Headers.h"   // Includes additional necessary headers (assuming common libraries or definitions)
#include "Methods.h"   // Includes additional methods needed for the Machine class

// The Machine class represents the main processing unit, containing memory, a CPU, and instructions
class Machine 
{
  private:
    Memory memoryMachine;           // An instance of the Memory class to manage machine memory
    CPU cpu;                        // An instance of the CPU class to manage CPU-related operations
    vector<string> Instructions;    // A vector to store the machine's instructions
    string StartIterate;            // Stores the starting address for iteration
    int InstSize ;

public:
    // Constructor: Initializes the Machine with instructions
  Machine(vector<string> Instruction) : Instructions(Instruction) { }

  // Loads instructions into memory, setting up the initial machine state
  void loadMemory(vector<string> Instructions);

  // Loads and executes the program stored in memory
  void loadProgram();

  // Outputs the current state of the machine's memory and CPU registers
  void stateOut();

  // Friend function: Allows DisplayMemory to access The Memory of Machine
  friend void DisplayMemory(Memory Mem);

  // Runs the machine with the provided instructions
   void RunMachine();
   void setInstructions(vector<string>  Inst) ;
   string getStartIterate () ;
      bool IsHalt; // A flag indicating whether the machine has halted (true if halted)
};

#endif // MACHINE_H
