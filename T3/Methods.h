#ifndef _METHODS_H
#define _METHODS_H
#include "Headers.h"
#include <bitset>
using namespace std ;
bool IsPowerOf2(int num);
int stringToInt(const string &str) ;
void GenerateMemory(map<string , string > &m ) ;
void GenerateRegister(map<string , string > &r ) ;
string decToHex(int dec) ;
int hexToDec(string hex) ;
string hexToBin(const string& hex);
string GetPath();
string binToHex(const string &bin);
#endif