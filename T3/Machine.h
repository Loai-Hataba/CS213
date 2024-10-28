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
    public:
        Machine(vector<string> Instructions) : Instructions(Instructions){
            loadMemory(Instructions);
            loadProgram();
            stateOut();
            
        } 
        void loadMemory(vector<string> Instructions);
        void loadProgram();
        
        void stateOut();
};

#endif // MACHINE_H