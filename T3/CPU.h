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
        string programCounter = "00";
        bool skip = false;
        string instructionRegister="";
        Register reg;
        ALU alu;
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