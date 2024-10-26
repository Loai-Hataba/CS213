#ifndef CPU_H
#define CPU_H
using namespace std;
#include "Headers.h"
#include "Memory.h"
#include "Regist.h"
#include "CU.h"
// #include "Alu.h"         TO DO
// #include "Machine.h"     TO DO

class CPU
{
    private:
        int programCounter = 0;
        string instructionRegister="";
        Register reg;
        // ALU alu;         TO DO
        CU cu;
        void fetch(Memory &memory);
        vector<int> decode();
        void execute(vector<int> instruction, Memory &memory, Register reg);
    public:
        void control(Memory &memory);
        void print();
};
#endif // CPU_H