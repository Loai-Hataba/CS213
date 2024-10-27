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


// void ALU::add(string idx1, string idx2, string idx3, Register& reg) {
//     string val1 = reg.getCell(idx1);
//     string val2 = reg.getCell(idx2);
//     int res = val1 + val2;
//     reg.setCell(idx3, res);
// }