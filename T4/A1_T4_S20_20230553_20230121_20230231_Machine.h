#ifndef MACHINE_H
#define MACHINE_H // Include guard to prevent multiple inclusions of this header file

#include "A1_T4_S20_20230553_20230121_20230231_CPU.h"      // Includes the CPU class definition
#include "A1_T4_S20_20230553_20230121_20230231_Memory.h"    // Includes the Memory class definition
#include "A1_T4_S20_20230553_20230121_20230231_Headers.h"   // Includes additional necessary headers (assuming common libraries or definitions)
#include "A1_T4_S20_20230553_20230121_20230231_Methods.h"   // Includes additional methods needed for the Machine class

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
  void loadMemory(vector<string> Instructions);
  void loadProgram();
  // Outputs the current state of the machine's memory and CPU registers
  void stateOut();

  // Friend function: Allows DisplayMemory to access The Memory of Machine
  friend void DisplayMemory(Memory Mem);

  // Runs the machine with the provided instructions
   void RunMachine();
   void setInstructions(vector<string>  Inst) ;
   //string getStartIterate () ;
   bool IsHalt; // A flag indicating whether the machine has halted (true if halted)
};

#endif // MACHINE_H
