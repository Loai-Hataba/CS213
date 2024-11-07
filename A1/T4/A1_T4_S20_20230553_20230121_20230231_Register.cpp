#include "A1_T4_S20_20230553_20230121_20230231_Regist.h"
void Register::setCell(string RegAddress, string  value)
{
	   reg[RegAddress] = value;
	
}

string Register::getCell(string RegAddress)
{
	
	return reg[RegAddress];
}

map<string, string> Register::getReg()
{
    return reg;
}

