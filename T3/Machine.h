#ifndef MACHINE_H
#define MACHINE_H
#include "CPU.h"
#include "Memory.h"
#include "Headers.h"
#include "Methods.h"
#include "Menu.h"
#include <iostream>
#include <string>

class Machine{
    protected:
        Memory memoryMachine;
        CPU cpu;
        vector<string> Instructions;
        string StartIterate ; 
    public:
        Machine(vector<string> Instructions) : Instructions(Instructions){
          RunMachine(Instructions) ;
        } 
        void loadMemory(vector<string> Instructions);
        void loadProgram();
        void stateOut();
        friend void DisplayMemory(Memory Mem);
        void RunMachine(vector<string> Instructions);
        bool IsHalt ;
};

#endif // MACHINE_H