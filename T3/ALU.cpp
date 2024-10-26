#include "ALU.h"
#include "Regist.h"
#include "Headers.h"

//string ALU::hexToDec() {
//    if (!isValid(hexStr)) {
//        cout<<"buh"<<endl;
//    }
//
//    int decimalValue = stoi(hexStr, nullptr, 16);
//    return to_string(decimalValue);
//}
//
//string ALU::decToHex() {
//        int decimalValue = stoi(decStr);
//        string hexStr;
//
//        while (decimalValue > 0) {
//            int remainder = decimalValue % 16;
//            char hexChar = (remainder < 10) ? '0' + remainder : 'A' + (remainder - 10);
//            hexStr = hexChar + hexStr;
//            decimalValue /= 16;
//        }
//
//        return hexStr.empty() ? "0" : hexStr;
//}

bool ALU::isValid(string hexStr) {
    for (char ch : hexStr) {
        if (!((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F'))) {
            return false;
        }
    }
    return true;
}

void ALU::add(int idx1, int idx2, int idx3, Register& reg) {
    int val1 = reg.getCell(idx1);
    int val2 = reg.getCell(idx2);
    int res = val1 + val2;
    reg.setCell(idx3, res);
}