#include "Machine.h"
void Machine::loadMemory(vector<string> Instructions)
{
    cout << "Loading memory..." << endl;
    InstSize = Instructions.size() / 2; // Update InstSize based on the current instructions count

    // Find the starting address with an empty cell in memory (cell value "00")
    for (size_t i = 0; i < 16; i++)
    {
        char firstDigit = (i < 10) ? ('0' + i) : ('A' + (i - 10));
        for (size_t j = 0; j < 16; ++j)
        { // Second hex digit (0 to F)
            char secondDigit = (j < 10) ? ('0' + j) : ('A' + (j - 10));
            std::string key = std::string(1, firstDigit) + secondDigit;

            if (memoryMachine.getCell(key) == "C0")
            {
                j++;
                continue;
            }
            if (memoryMachine.getCell(key) == "00")
            {
                StartIterate = key;
                break; // Stop when the first empty cell is found
            }
        }
        if (!StartIterate.empty())
            break; // Exit outer loop if start is found
    }

    int Start_Dec = hexToDec(StartIterate); // Convert the starting address to decimal

    // Load instructions into memory starting from the available cell
    for (size_t i = 0; i < Instructions.size(); i++)
    {
        int address = Start_Dec + i;
        std::string hexAddress = decToHex(address);
        memoryMachine.setCell(hexAddress, Instructions[i]);
        cout << memoryMachine.getCell(hexAddress) << " ";
    }
}

void Machine::loadProgram()
{
    // Convert the starting address to decimal
    int Start_Dec = hexToDec(StartIterate);
    cout << "Start Address (Decimal): " << Start_Dec << endl;

    // Loop through the instructions
    int end = InstSize + Start_Dec;
    cout << "Instruction Count = " << InstSize << endl;

    for (int i = Start_Dec; i < end; i++)
    {
        cpu.control(memoryMachine);

        // Check if CPU has halted
        if (cpu.IsHalt)
        {
            IsHalt = true;          // Set machine's halt flag
            cpu.IsHalt = false;     // Reset CPU's halt flag if necessary
            cout << "Halt" << endl; // Print halt message
            break;
        }

        // Debug: Output current address
        cout << "Current Address (Decimal): " << i << endl;
    }

    cout << "Loading program..." << endl;
}

//////////////////////////////////////////////////////////////////
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

    //////////////////////////////////////////////////////////////////

    void Machine::stateOut()
    {
        cout << "state out...\n";
        DisplayMemory(memoryMachine);
        cout << endl
             << endl;
        cpu.DisplayRegister();
   
}
//////////////////////////////////////////////////////////////////
void Machine::RunMachine(vector<string> Instructions)
{
    loadMemory(Instructions);
    loadProgram();
    stateOut();
}

