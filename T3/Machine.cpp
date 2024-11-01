#include "Machine.h"
void Machine::loadMemory(vector<string> Instructions)
{
    cout << "Loading memory..." << endl;
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
    cout <<endl;  
}

void Machine::loadProgram()
{
    // Convert the starting address to decimal
    int Start_Dec = hexToDec(StartIterate);
    cout << "Loading program..." << endl; // Moved to the beginning
    cout << "Start Address (Decimal): " << Start_Dec << endl;

    // Calculate end of instructions
    int end = InstSize + Start_Dec;
    cout << "Instruction Count = " << InstSize << endl;

    for (int i = Start_Dec; i < end; i++)
    {
        cpu.control(memoryMachine);

        // Handle jump if specified
        if (cpu.IsJump != 0)
        {
            i += cpu.IsJump - 1; // Adjust for loop increment
            cout << "Jump : " << cpu.IsJump << endl;
            cpu.IsJump = 0;
        }

        // Check if CPU has halted
        if (cpu.IsHalt)
        {
            IsHalt = true;          // Set machine's halt flag
            cout << "Halt" << endl; // Print halt message
            break;
        }

        // Debug: Output current address if needed
        // cout << "Current Address (Decimal): " << i << endl;
    }
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
        cout << endl<< endl;
        cpu.DisplayRegister();
   
}
//////////////////////////////////////////////////////////////////
void Machine::RunMachine()
{
    InstSize = Instructions.size() / 2 ;
    loadMemory(Instructions);
    loadProgram();
    stateOut();
}

void Machine::setInstructions(vector<string> Inst)
{
    Instructions = Inst ;
}

string Machine::getStartIterate()
{
    return StartIterate;
}
