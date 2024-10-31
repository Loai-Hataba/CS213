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
string addBin(string bin1, string bin2);
string subBin(const string& bin1, const string& bin2);
char GetChoice(const string &Message, const string &Choices, char Start, char End) ;
string GetFileContent() ;
bool CheckInst(string Inst) ;
vector<string> ExtractInst() ;
#endif