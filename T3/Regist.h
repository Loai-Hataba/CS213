#pragma once
#include"Headers.h"
using namespace std ;
class Register
{
private:
	vector <int>reg ;
	int size;
public:
	Register();
	Register(int S);
	void setCell(int address, int value);
	int getCell(int address);
	void setSize(int S);
	int GetSize() ;
	friend bool IsPowerOf2(int num);

};

