#include "A1_T4_S20_20230553_20230121_20230231_Memory.h"



map<string, string> Memory::getMemory()
{
    return memory;
}

void Memory::setCell(string address, string value)
{
   
    memory[address] = value ;
    
}

string Memory::getCell(string address)
{
   
       return memory[address] ;
}

