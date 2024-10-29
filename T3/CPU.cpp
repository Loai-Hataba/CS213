#include "CPU.h"


void CPU::fetch(Memory & memory){
    //read the instruction from memory
    int tempPCIR  = hexToDec(programCounter);
    tempPCIR += 1;
    string finalPCIR = decToHex(tempPCIR);
    instructionRegister = memory.getCell(programCounter) + memory.getCell(finalPCIR);
    int temp_PC = hexToDec(programCounter);
    temp_PC += 2;
    if (temp_PC > 256)
    {
        cout << "Memory Full!" << endl;
    }
    //FIXME: handle overflow
    programCounter = decToHex(temp_PC);
}

vector<string> CPU::decode(){
    string opCodeHex = instructionRegister.substr(0, 1);
    string R_Hex= instructionRegister.substr(1, 1);
    string XY_Hex = instructionRegister.substr(2, 2);
    string X_Hex = instructionRegister.substr(2, 1);
    string Y_Hex = instructionRegister.substr(3, 1);
    return {opCodeHex, R_Hex, XY_Hex , X_Hex ,Y_Hex };
    // decode the instruction
}

void CPU::execute(vector<string> instruction, Memory & memory){
    // Execute the instruction
    char OpCode = instruction[0][0];
    string idxReg = instruction[1];
    string idxXY = instruction[2];    
    string idxX = instruction[3];    
    string idxY = instruction[4];
    cout << "Instruction: " << OpCode << " " << idxReg << " " << idxXY << std::endl;
    switch (OpCode)
    {
    case '1':
        cu.Load(idxReg, idxXY, reg, memory);
        break;

    case '2':
        cu.Load(idxReg, idxXY, reg);
        break;

    case '3':
        cu.Store(idxReg, idxXY, reg, memory);
        break;

    case '4':
    {
        if (idxReg[0] == '0')
        { // Check for valid format 0RS
            cu.Move(idxX,idxY , reg);
        }
        else
        {
            std::cerr << "Error: Invalid MOVE instruction format" << std::endl;
        }
    }
    break;
    case '5':
        idxX = "0" + idxX;
        idxY = "0" + idxY;
        alu.add(idxReg, idxX, idxY, reg);       
        break; 
    case 'B':
        cu.Jump(idxReg, idxXY, reg, programCounter);
        break;

    case 'C':
        cu.Halt();
        break;

    default:
        std::cout << "Invalid OP Code !!" << std::endl;
        break;
    }
}

//orchestrate all of the processes
void CPU::control(Memory & memory){
    fetch(memory);
    vector<string> decoded = decode();
    execute(decoded, memory);
}

void CPU :: DisplayRegister()
{
    for (size_t i = 0; i < 16; i++)
    {
        string ch;
        if (i >= 10 && i <= 15)  ch = static_cast<char>('A' + (i - 10)); // Converts 10-15 to 'A'-'F'
        else   ch = static_cast<char>('0' + i); // Converts 0-9 to '0'-'9'
        cout << "R" << ch << "    " << reg.getCell(ch)  << endl;
    }
}
void CPU::print(){
    cout << "CPU is working." << endl;
}

Register CPU::GetRegister()
{
    return reg;
}
