#pragma once
#include "Headers.h"
using namespace std ;
class Memory
{
private :
	map <string , string> memory;
	// address is -- > address 
	// value is -- > stored 
public :
	Memory();
	map<string ,string> getMemory() ;
	void setCell(string address, string value);
	string getCell(string address);
	
};

