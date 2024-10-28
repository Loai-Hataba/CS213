#include "Machine.h"

void Machine::loadMemory(vector<string> Instructions) {
    cout << "Loading memory..." << endl;
    for (int i = 0; i < Instructions.size(); i++) {
        memoryMachine.setCell(decToHex(i), Instructions[i]);
        cout << memoryMachine.getCell(decToHex(i)) << " \n";
    }
}
//TODO: FIX Halt function in Machine class
void Machine::loadProgram(){
    for (int i = 0; i < (Instructions.size() / 2); i++) {
        cpu.control(memoryMachine);
    }
    // cpu.control(memory, reg);
    cout << "Loading program..." << endl;
}

void Machine::stateOut()
{
    //TODO: Implement state output
    cout << "state out...\n";
}