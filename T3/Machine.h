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
        CPU cpu;
        Memory memory;
    public:
        void loadProgram(string fileName);

        void stateOut();
};

#endif // MACHINE_H