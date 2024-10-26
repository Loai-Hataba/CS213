#include "Memory.h"

Memory::Memory()
{
    memory = {};
}

Memory::Memory(int S)
{
    if (IsPowerOf2(S))
    {
        size = S ;
        memory = vector<string>(size, "");
    }
    else
        cout << "Error : Invalid Memory Size It Must be Power Of 2 --> (2,4,8,16 ....) " << endl;
}

void Memory::setCell(int address, string value)
{
    if(address < size  &&  address >= 0) 
    {
        memory[address] = value ;
    } 
    else cout << "Error : Invalid Address must be ( 0 - " <<size <<  " )" <<endl; 
}

string Memory::getCell(int address)
{
    if (address < size && address >= 0)
    {
        return memory [address] ;
    }
    else
    {
        cout << "Error : Invalid Address must be ( 0 - " << size << " )" << endl;
        return "" ;
    }
}

void Memory::setSize(int S)
{
    if (IsPowerOf2(S))
    {
        size = S; 
        memory = vector<string>(size, "");
    }
    else
        cout << "Error : Invalid Memory Size It Must be Power Of 2 --> (2,4,8,16 ....) " << endl;
}

int Memory::GetSize()
{
    return size ;
}