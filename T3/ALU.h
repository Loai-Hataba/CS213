#include "Headers.h"
#include "Regist.h"
#include "Methods.h"
#include <bitset>

class ALU {
public:
    void add(string idx1, string idx2, string idx3, Register& reg);
    void floatingAdd(string idx1, string idx2, string idx3, Register& reg); //not yet
};