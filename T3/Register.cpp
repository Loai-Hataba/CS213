#include "Regist.h"

Register::Register()
{
	reg = {} ;
}

Register::Register(int S)
{
	if (IsPowerOf2(S))
	{
		size = S ;
		reg = vector<int>(size, 0);
	}
	else
		cout << "Error : Invalid Memory Size It Must be Power Of 2 --> (2,4,8,16 ....) " << endl;
}

void Register::setCell(int address, int value)
{
	if (address <= size && address >= 0)
	{
		reg[address] = value;
	}
	else
		cout << "Error : Invalid Address must be ( 0 - " << size << " )" << endl;
}

int Register::getCell(int address)
{
	if (address < size && address >= 0)
	{
		return reg[address];
	}
	else
	{
		cout << "Error : Invalid Address must be ( 0 - " << size << " )" << endl;
		return 0 ;
	}
}

void Register::setSize(int S)
{
	if (IsPowerOf2(S))
	{
		size = S ;
		reg = vector<int>(size , 0);
	}
	else
		cout << "Error : Invalid Memory Size It Must be Power Of 2 --> (2,4,8,16 ....) " << endl;
}

int Register::GetSize()
{
    return size;
}