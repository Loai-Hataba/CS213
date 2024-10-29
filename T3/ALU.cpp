#include "ALU.h"



void ALU::add(string idx1, string idx2, string idx3, Register& reg) {
    string bin1 = hexToBin(reg.getCell(idx2));
    string bin2 = hexToBin(reg.getCell(idx3));

    string res = addBin(bin1, bin2);

    reg.setCell(idx1, res);
}

void ALU::floatingAdd(string idx1, string idx2, string idx3, Register& reg){ //not yet cuh
    string bin1 = hexToBin(reg.getCell(idx2));
    string bin2 = hexToBin(reg.getCell(idx3));
    string sign1 = bin1.substr(0,1);
    string sign2 = bin2.substr(0,1);
    string exp1 = bin1.substr(1,3);
    string exp2 = bin2.substr(1,3);
    string man1 = bin1.substr(4);
    string man2 = bin2.substr(4);
}