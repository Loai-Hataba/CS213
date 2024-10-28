#include "Machine.h"

void Machine::loadMemory(vector<string> Instructions) {
    cout << "Loading memory..." << endl;
    for (int i = 0; i < Instructions.size(); i++) {
        memoryMachine.setCell(decToHex(i), Instructions[i]);
        cout << memoryMachine.getCell(decToHex(i)) << " \n";
    }
}

void Machine::loadProgram(){
    for (int i = 0; i < (Instructions.size() / 2); i++) {
        cpu.control(memoryMachine);
    }
    // cpu.control(memory, reg);
    cout << "Loading program..." << endl;
}
void DisplayMemory(Memory Mem)
{
    for (size_t i = 0; i < 16; i++)
    {
        if (i >= 10 && i <= 15)
        {
            cout << static_cast<char>('A' + (i - 10)) << "     ";
        }
        else
        {
            cout << i << "    ";
        }
    }

    cout << endl << endl;    
    for (size_t i = 0; i < 16; i++)
    {
        if (i >= 10 && i <= 15)
        {
            cout << static_cast<char>('A' + (i - 10)) << "    ";
        }
        else
        {
            cout << i << "    ";
        }
        for (size_t i = 0; i < 16; i++)
        {
            cout << Mem.getCell(decToHex(i)) << "   ";
        }
        cout << endl; 
        }
    }

void Machine::stateOut()
{
    cout << "state out...\n";
    DisplayMemory(memoryMachine) ;
    cout << endl <<endl;  
   
}

