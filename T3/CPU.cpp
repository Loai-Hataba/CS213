#include "CPU.h"

void CPU::fetch(Memory & memory){
    //read the instruction from memory
    instructionRegister = memory.getCell(programCounter);
    if (instructionRegister.length() <= 3 || instructionRegister.length() > 4){
    //TODO: add instruction check (skip instruction lines)

    }
    programCounter++;
    std::cout << "PC: " << programCounter << std::endl;
}


vector<int> CPU::decode(){
    string opCodeHex = instructionRegister.substr(0, 1);
    string operandHex = instructionRegister.substr(1, 1);
    string operandTempHex = instructionRegister.substr(2, 2);
    int opCode = stoi(opCodeHex, nullptr, 16);
    int R = stoi(operandHex, nullptr, 16);
    int XY = stoi(operandTempHex, nullptr, 16);
    std::cout << "Instruction: " << opCode << " " << R << " " << XY << std::endl;
    return {opCode, R, XY};
    // decode the instruction
}



void CPU::execute(vector<int> instruction, Memory & memory, Register reg){
    // Execute the instruction
    int OpCode = instruction.front();
    int idxReg = instruction[1];
    int idxXY = instruction.back();

    // Move the variable initialization outside the switch statement
    int regSource = (idxXY / 100) % 10; // Extract source register (R)
    int regDest = idxXY % 10; 
    std:: cout << "X: " << regSource << "Y: " << regDest << endl;         // Extract destination register (S)

    switch (OpCode)
    {
    case 1:
        cu.Load(idxReg, idxXY, reg, memory);
        break;

    case 2:
        cu.Load(idxReg, idxXY, reg);
        break;

    case 3:
        cu.Store(idxReg, idxXY, reg, memory);
        break;

    case 4:
    {
        if (idxReg == 0)
        { // Check for valid format 0RS
            cu.Move(regSource, regDest, reg);
            std::cout << "MOVE: Moved value from register " << regSource << " to register " << regDest << std::endl;
        }
        else
        {
            std::cerr << "Error: Invalid MOVE instruction format" << std::endl;
        }
    }
    break;

    case 11:
        cu.Jump(idxReg, idxXY, reg, programCounter);
        break;

    case 12:
        cu.Halt();
        break;

    default:
        std::cout << "Invalid OP Code !!" << std::endl;
        break;
    }
}

void CPU::control(Memory & memory){
    //orchestrate all of the processes
    fetch(memory);
    decode();
}

void CPU::print(){
    cout << "CPU is working." << endl;
}

int main()
{
    CPU cpu;
    Memory memory;
    memory.setSize(4);
    memory.setCell(0, "1204");
    memory.setCell(1, "5018");
    memory.setCell(2, "12A3");
    cpu.control(memory);
    cpu.control(memory);
    cpu.control(memory);
    Register registers(16);
    cpu.print();
    return 0;
}