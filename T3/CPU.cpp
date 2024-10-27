#include "CPU.h"


void CPU::fetch(Memory & memory){
    skip = false;
    //read the instruction from memory
    
    cout << "PC: " << programCounter << endl;
    instructionRegister = memory.getCell(programCounter);
    if (instructionRegister.length() != 4){
    cout << instructionRegister << endl;
    cout <<"------------------------------------\n";
    regex patternREGEX(R"(^[0-6BC][0-9A-F]{3}$)");
    if (!regex_match(instructionRegister, patternREGEX)) {
        skip = true;
    //TODO: add instruction check (skip instruction lines)
    //TODO: turn memory, instructions into HEXA

    }
    //TODO: turn memory, instructions into HEXA
    // programCounter++; FIXME:
    std::cout << "PC: " << programCounter << endl <<" skip: " << skip << std::endl;
}
    int temp_PC = hexToDec(programCounter);
    temp_PC += 2;
    programCounter = decToHex(temp_PC);
    cout << "PC: " << programCounter << endl <<" skip: " << skip << std::endl;

}

vector<string> CPU::decode(){
    // 1 2 34, 3 4
    cout << "yarab\n";
    cout << "1\n";
    cout << instructionRegister << endl;
    string opCodeHex = instructionRegister.substr(0, 1);
    cout << "2\n";
    cout << instructionRegister.substr(1, 1) << endl;
    string R_Hex= instructionRegister.substr(1, 1);
    cout << "3\n";
    string XY_Hex = instructionRegister.substr(2, 2);
    cout << "4\n";
    string X_Hex = instructionRegister.substr(2, 1);
    cout << "5\n";
    string Y_Hex = instructionRegister.substr(3, 1);
    // int opCode = 0;
    // int R = stoi(R_Hex, nullptr, 16);
    //FIXME: turn skip line to check hexa
    // try {
    //     opCode = stoi(opCodeHex, nullptr, 16);
    //     if ((opCode < 0 || opCode > 6) && opCode != 11 && opCode != 12){
    //         skip = true;
    //     }
        
    // } catch (const std::invalid_argument& ia) {
    //     skip = true;
    // }
    // int XY = stoi(XY_Hex, nullptr, 16);
    // int X = stoi(X_Hex, nullptr, 16);
    // int Y = stoi(Y_Hex, nullptr, 16);
    std::cout << "Instruction: " << opCodeHex << " " << R_Hex << " " << XY_Hex << std::endl;
    return {opCodeHex, R_Hex, XY_Hex , X_Hex ,Y_Hex };
    // decode the instruction
}

void CPU::execute(vector<string> instruction, Memory & memory, Register &reg){
    // Execute the instruction
    char OpCode = instruction[0][0];
    string idxReg = instruction[1];
    string idxXY = instruction[2];    
    string idxX = instruction[3];    
    string idxY = instruction[4];
    if (skip) {return;}
    if (skip) {cout << "skipped" << endl; return;}
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
            //std::cout << "MOVE: Moved value from register " << idxX << " to register " << idxY << std::endl;
        }
        else
        {
            std::cerr << "Error: Invalid MOVE instruction format" << std::endl;
        }
    }
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
void CPU::control(Memory & memory, Register &reg){
    fetch(memory);
    vector<string> decoded = decode();
    execute(decoded, memory, reg);
}

void CPU::print(){
    cout << "CPU is working." << endl;
}

void CPU::DisplayMemory(Memory m)
{
    for (size_t i = 0; i < 256; i++)
    {
        cout << "i = " << i << endl;
        string i_Hex;
        if (i < 10)
        {
            i_Hex = to_string(0);
        }
        i_Hex += decToHex(i);
        cout << m.getCell(i_Hex) << endl;
    }
}

int main()
{
    CPU cpu;
    Memory memory;
    Register reg;
    memory.setCell("00", "1224");
    // memory.setCell("1", "4018");
    memory.setCell("02", "4018");
    // memory.setCell("2", "12A3");
    // memory.setCell("3", "X2A3");
    memory.setCell("04", "X2A3");
    // memory.setCell("4", "32A3");
    cpu.control(memory, reg);
    // cpu.control(memory, reg);
    // cpu.control(memory, reg);
    cpu.control(memory, reg);
    cpu.control(memory, reg);
    cpu.print();
    cpu.DisplayMemory(memory) ;
    for (size_t i = 0; i < 256; i++)
    {
        cout << "i = " << i << endl;
        string i_Hex = decToHex(i);
        cout << memory.getCell(i_Hex) <<endl; 
    }
    
    return 0;
}