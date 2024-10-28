#pragma once
#include"Headers.h"
using namespace std ;
class Register
{
private:
	map <string , string >reg ;
	
public:
	void setCell(string RegAddress, string  value);
	string  getCell(string RegAddress);
	map<string , string > getReg () ;
};

