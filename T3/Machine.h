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
    private:
        Memory memory;
        ALU alu;
        CU cu;
        CPU cpu;
        Register reg;
        string path;
    public:
        Machine(string path) : path(path), cpu(cu, alu, reg, memory){} 
        void loadProgram(vector<string> Instructions);
        
        void stateOut();
};

#endif // MACHINE_H