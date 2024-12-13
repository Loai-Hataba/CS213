
#ifndef METHODS_H
#define METHODS_H
#include <iostream>
#include <limits>
#include <string>
#include <iomanip>
#include <map>

using namespace std;
int getPlayerType();
string getPlayerName(int PlayerNum);
int getValidIndex(const string &message, int start, int end);
bool isInteger(string str);

#endif // METHODS_H
