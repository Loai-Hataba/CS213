#include "CPU.h"

void CPU::fetch(Memory & memory){
    //read the instruction from memory
    instructionRegister = memory.getCell(programCounter);
    //TODO: add instruction check (skip instruction lines)
    programCounter++;
    std::cout << "PC: " << programCounter << std::endl;
}

int combine(int a, int b){
    // combine two operands
    //TODO: preseve 0 (1011-> 1 "0"11)
    string A = to_string(a);
    string B = to_string(b);
    string combined = A + B;
    return stoi(combined);
}
vector<int> CPU::decode(){
    string opCodeHex = instructionRegister.substr(0, 1);
    string operandHex = instructionRegister.substr(1, 1);
    string operandTempHex = instructionRegister.substr(2,2);
    int opCode = stoi(opCodeHex, nullptr, 16);
    int operand = stoi(operandHex, nullptr, 10);
    std::cout << operand << std::endl;
    int operandTemp = stoi(operandTempHex, nullptr, 16);
    operand = combine(operand, operandTemp);
    std:: cout << "instruction: " << opCode << " " << operand << std::endl;
    return {opCode, operand};
    //decode the instruction
}



void CPU::execute(vector<int> instruction, Memory & memory, Register reg){
    // execute the instruction
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