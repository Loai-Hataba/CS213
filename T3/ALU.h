#include "Headers.h"
#include "Regist.h"

class ALU {
    public:
        string hexToDec();
        string decToHex();
        bool isValid(string hexStr);
        void add(int idx1, int idx2, int idx3, Register& reg);
};