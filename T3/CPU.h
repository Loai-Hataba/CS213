#ifndef CPU_H
#define CPU_H
using namespace std;
#include "Headers.h"
#include "Memory.h"
#include "Regist.h"
#include "CU.h"
#include "Methods.h"
#include "Alu.h"
#include "Machine.h"
#include "Menu.h"
#include <string>
#include <regex>

class CPU
{
    private:
        CU cu;
        ALU alu;
        Register& reg;
        Memory& memory;
        string programCounter = "00";
        bool skip = false;
        string instructionRegister="";
        void fetch(Memory &memory);
        vector<string> decode();
        void execute(vector<string> instruction, Memory &memory, Register& reg);
    public:
        CPU(CU cu, ALU alu, Register& reg, Memory& memory) : cu(cu), alu(alu), reg(reg), memory(memory){}
        void control(Memory &memory, Register &reg);
        void print();
        void DisplayMemory(Memory m ) ;
};
#endif // CPU_H