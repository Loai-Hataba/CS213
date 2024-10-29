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
    cout << "     ";
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
    }

    cout << endl << endl;    
    for (size_t i = 0; i < 16; i++)
    {
        // Print The Top Row Of Indices 
        if (i >= 10 && i <= 15)
        {
            cout << static_cast<char>('A' + (i - 10)) << "    ";
        }
        else
        {
            cout << i << "    ";
        }
        ///
        /// Get The Right Address 
        char firstDigit;
        if (i < 10)
        {
            firstDigit = '0' + i; // '0' to '9'
        }
        else
        {
            firstDigit = 'A' + (i - 10); // 'A' to 'F'
        }

        for (size_t j = 0; j < 16; ++j) // Second hex digit (0 to F)
        {
            char secondDigit;
            if (j < 10)
            {
                secondDigit = '0' + j; // '0' to '9'
            }
            else
            {
                secondDigit = 'A' + (j - 10); // 'A' to 'F'
            }
            // Printing Cells With The Right Address
            std::string key = std::string(1, firstDigit) + secondDigit;
            cout << Mem.getCell(key )<< "   "; 
        }
        cout << endl; 
        }
    }



void Machine::stateOut()
{
    cout << "state out...\n";
    DisplayMemory(memoryMachine) ;
    cout << endl <<endl;  
    cpu.DisplayRegister() ;
   
}

