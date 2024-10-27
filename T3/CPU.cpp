#include "CPU.h"

void CPU::fetch(Memory & memory){
    skip = false;
    //read the instruction from memory
    instructionRegister = memory.getCell(programCounter);
    if (instructionRegister.length() != 4){
        skip = true;
    //TODO: add instruction check (skip instruction lines)

    }
    programCounter++;
    std::cout << "PC: " << programCounter << " skip: " << skip << std::endl;
    std::cout << "PC: " << programCounter << endl <<" skip: " << skip << std::endl;
}


vector<int> CPU::decode(){
    string opCodeHex = instructionRegister.substr(0, 1);
    string R_Hex= instructionRegister.substr(1, 1);
    string XY_Hex = instructionRegister.substr(2, 2);
    string X_Hex = instructionRegister.substr(2, 1);
    string Y_Hex = instructionRegister.substr(3, 1);
    int opCode = 0;
    int R = stoi(R_Hex, nullptr, 16);
    
    try {
        opCode = stoi(opCodeHex, nullptr, 16);
        if ((opCode < 0 || opCode > 6) && opCode != 11 && opCode != 12){
            skip = true;
        }
        
    } catch (const std::invalid_argument& ia) {
        skip = true;
    }
    cout << "skip_2: " << skip << std::endl;
    cout << "skip_2: " << skip << std::endl <<endl; 
    int XY = stoi(XY_Hex, nullptr, 16);
    int X = stoi(X_Hex, nullptr, 16);
    int Y = stoi(Y_Hex, nullptr, 16);
    std::cout << "Instruction: " << opCode << " " << R << " " << XY << std::endl;
    return {opCode, R, XY , X ,Y };
    // decode the instruction
}

void CPU::execute(vector<int> instruction, Memory & memory, Register &reg){
    // Execute the instruction
    int OpCode = instruction.front();
    int idxReg = instruction[1];
    int idxXY = instruction[2];    
    int idxX = instruction[3];    
    int idxY = instruction[4];  
    //FIXME: fix PC incrementation to out of bounds memory (256)
    if (skip) {return;}
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
            cu.Move(idxX,idxY , reg);
            //std::cout << "MOVE: Moved value from register " << idxX << " to register " << idxY << std::endl;
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

void CPU::control(Memory & memory, Register &reg){
    //orchestrate all of the processes
    fetch(memory);
    vector<int> decoded = decode();
    execute(decoded, memory, reg);
}

void CPU::print(){
    cout << "CPU is working." << endl;
}

int main()
{
    CPU cpu;
    Memory memory;
    Register reg(16);
    memory.setSize(8);
    memory.setCell(0, "1214");
    memory.setCell(1, "A018");
    memory.setCell(2, "X123");
    memory.setCell(3, "12A3");
    cpu.control(memory, reg);
=======
    memory.setSize(256);
    memory.setCell(0, "1224");
    memory.setCell(1, "4018");
    memory.setCell(2, "12A3");
    memory.setCell(3, "X2A3");
    memory.setCell(4, "32A3");
>>>>>>> Stashed changes
    cpu.control(memory, reg);
    cpu.control(memory, reg);
    cpu.control(memory, reg);
    cpu.print();
    return 0;
}