#ifndef CPU_H
#define CPU_H
using namespace std;
#include "Headers.h"
#include "Memory.h"
#include "Regist.h"
#include "CU.h"
// #include "Alu.h"         TODO:
// #include "Machine.h"     TODO:

class CPU
{
    private:
        int programCounter = 0;
        bool skip = false;
        string instructionRegister="";
        Register reg;
        // ALU alu;         TODO:
        CU cu;
        void fetch(Memory &memory);
        vector<int> decode();
        void execute(vector<int> instruction, Memory &memory, Register reg);
        void execute(vector<int> instruction, Memory &memory, Register& reg);
    public:
        void control(Memory &memory, Register reg);
        void print();
};
#endif // CPU_H