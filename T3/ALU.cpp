#include "ALU.h"



void ALU::add(string idx1, string idx2, string idx3, Register& reg) {
     string bin1 = hexToBin(reg.getCell(idx2));
     string bin2 = hexToBin(reg.getCell(idx3));

     string res_bin = addBin(bin1, bin2);
     string res = binToHex(res_bin);

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

     int iexp1 = stoi(exp1, nullptr, 2);
     int iexp2 = stoi(exp2, nullptr, 2);

     while (iexp1 < iexp2) {
         man1 = "0" + man1.substr(0, man1.size() - 1); // Shift right
         iexp1++;
     }
     while (exp2 < exp1) {
         man2 = "0" + man2.substr(0, man2.size() - 1); // Shift right
         iexp2++;
     }

     exp1 = bitset<3>(iexp1).to_string();

     string resExp = exp1; // Exponents are aligned
     string resMan;
     string resSign;

     resSign = sign1;
     resMan = addBin(man1, man2);
     cout<<"resman "<<resMan<<endl;

     // Normalize if mantissa exceeds 5 bits
     if (resMan.size() > 5) {
         resMan = resMan.substr(1); // Drop the leading bit
         int exp = stoi(resExp, nullptr, 2) + 1;
         resExp = bitset<3>(exp).to_string();
     }

     // Truncate mantissa back to 4 bits (implicit 1 is not stored)
     resMan = resMan.substr(1, 4);
     string res = resSign+resExp+resMan;
     cout<<"binary float res:"<< res <<endl;
     reg.setCell(idx1,res);
}