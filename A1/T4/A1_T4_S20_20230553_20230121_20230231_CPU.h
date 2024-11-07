#ifndef CPU_H
#define CPU_H
using namespace std;
#include "A1_T4_S20_20230553_20230121_20230231_Headers.h"
#include "A1_T4_S20_20230553_20230121_20230231_Memory.h"
#include "A1_T4_S20_20230553_20230121_20230231_Regist.h"
#include "A1_T4_S20_20230553_20230121_20230231_CU.h"
#include "A1_T4_S20_20230553_20230121_20230231_Methods.h"
#include "A1_T4_S20_20230553_20230121_20230231_Alu.h"
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
        void fetch(Memory &memory  );
        vector<string> decode();
        void execute(vector<string> instruction, Memory &memory);
   
    public:
        void control(Memory &memory  );
        void print();
        void DisplayRegister() ;
        Register GetRegister() ;
        void setPc(string pc) ; 
        bool IsHalt  ;
        int IsJump  ;
        CPU(){ IsHalt = false , IsJump = 0 ; }
       
};
#endif // CPU_H