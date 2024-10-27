#ifndef CPU_H
#define CPU_H
using namespace std;
#include "Headers.h"
#include "Memory.h"
#include "Regist.h"
#include "CU.h"
#include <string>
// #include "Alu.h"         TODO:
// #include "Machine.h"     TODO:

class CPU
{
    private:
        string programCounter = "00";
        bool skip = false;
        string instructionRegister="";
        Register reg;
        // ALU alu;         TODO:
        CU cu;
        void fetch(Memory &memory);
        vector<string> decode();
        void execute(vector<string> instruction, Memory &memory, Register& reg);
    public:
        void control(Memory &memory, Register &reg);
        void print();
        void DisplayMemory(Memory m ) ;
};
#endif // CPU_H