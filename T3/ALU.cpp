#include "ALU.h"



void ALU::add(string idx1, string idx2, string idx3, Register& reg) {

    // Convert hexadecimal to binary for binary addition
    string bin1 = hexToBin(reg.getCell(idx2));
    string bin2 = hexToBin(reg.getCell(idx3));

    // Perform binary addition
    string result_bin;
    int carry = 0;
    int len = max(bin1.size(), bin2.size());

    // Extend both binary strings to the same length with sign extension
    string b1 = string(len - bin1.size(), bin1[0]) + bin1;
    string b2 = string(len - bin2.size(), bin2[0]) + bin2;
    // Add binary strings from the last bit to the first
    for (int i = len - 1; i >= 0; --i) {
        int bit1 = b1[i] - '0';
        int bit2 = b2[i] - '0';
        int sum = bit1 + bit2 + carry;
        result_bin = char((sum % 2) + '0') + result_bin;
        carry = sum / 2;
    }

    if (carry == 1) {
        result_bin = "1"+result_bin;
    }
    string res = binToHex(result_bin);
    reg.setCell(idx1, res);
}

void ALU::floatingAdd(string idx1, string idx2, string idx3, Register& reg){
    double val1 = hexToDec(reg.getCell(idx2));
    double val2 = hexToDec(reg.getCell(idx3));

}