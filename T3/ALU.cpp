#include "ALU.h"
#include "Headers.h"

string hexToBin(const string& hex) {
    std::string bin;
    for (char ch : hex) {
        int n = (ch >= '0' && ch <= '9') ? ch - '0' : ch - 'A' + 10;
        bin += std::bitset<4>(n).to_string();
    }
    cout<<"bin:"<<bin<<endl;
    return bin;
}

// Convert binary string to hex string
string binToHex(const string& bin) {
    int  dec = stoi(bin, nullptr,2);
    cout<<"decimal :"<<dec<<endl;
    string hex = decToHex(dec);
    cout<<"hex :"<<hex<<endl;
    return hex;
}

void ALU::add(string idx1, string idx2, string idx3, Register& reg) {
    string bin1 = hexToBin(reg.getCell(idx2));
    string bin2 = hexToBin(reg.getCell(idx3));
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