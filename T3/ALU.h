#include "Headers.h"
#include "Regist.h"
#include <bitset>

class ALU {
public:
    string hexToBin(const string& hex);
    string binToHex(const string& bin);
    void add(string idx1, string idx2, string idx3, Register& reg);
    void floatingAdd(string idx1, string idx2, string idx3, Register& reg);
};