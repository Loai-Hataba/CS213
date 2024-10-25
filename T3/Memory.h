#pragma once
#include "Headers.h"
using namespace std ;
class Memory
{
private :
	vector <string> memory;
	int size  ;
public :
	Memory();
	Memory(int S);
	void setCell(int address, string value);
	string getCell(int address);
	void setSize(int S);
	int GetSize() ;
	friend bool IsPowerOf2(int num);
	
};

