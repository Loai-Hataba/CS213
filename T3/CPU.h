#ifndef CPU_H
#define CPU_H
using namespace std;
#include "Headers.h"
#include "Memory.h"
#include "Regist.h"
#include "CU.h"
#include "Methods.h"
#include "Alu.h"
#include <string>
#include <regex>

class CPU
{
    private:
        CU cu;
        ALU alu;
        Register reg;
        string programCounter = "00";
        bool skip = false;
        string instructionRegister="";
        void fetch(Memory &memory);
        vector<string> decode();
        void execute(vector<string> instruction, Memory &memory);
    public:
        void control(Memory &memory);
        void print();
        void DisplayRegister() ;
        Register GetRegister() ;
        bool IsHalt  ;
};
#endif // CPU_H