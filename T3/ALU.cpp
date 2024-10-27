#include "ALU.h"
#include "Headers.h"


 void ALU::add(string idx1, string idx2, string idx3, Register& reg) {
     int val1 = hexToDec(reg.getCell(idx2));
     int val2 = hexToDec(reg.getCell(idx3));
     while (val2 != 0) {
         int carry = val1 & val2;
         val1 = val1 ^ val2;
         val2 = carry << 1;
     }
     string res = decToHex(val1);
     reg.setCell(idx1, res);
 }

 void ALU::floatingAdd(string idx1, string idx2, string idx3, Register& reg){
     double val1 = hexToDec(reg.getCell(idx2));
     double val2 = hexToDec(reg.getCell(idx3));

}