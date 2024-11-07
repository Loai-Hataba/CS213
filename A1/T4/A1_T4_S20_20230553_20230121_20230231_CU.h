#ifndef _CU_H
#define _CU_H
#include "A1_T4_S20_20230553_20230121_20230231_Headers.h"
#include "A1_T4_S20_20230553_20230121_20230231_Regist.h"
#include "A1_T4_S20_20230553_20230121_20230231_Memory.h"
class CU
{
public:
void Load (string idxReg , string MemAddress , Register &R , Memory &M) ;
void Load (string idxReg , string value , Register &R ) ;
void Store (string idxReg , string MemAddress, Register &R , Memory & M ) ;
void Move (string idxReg1 , string idxReg2 , Register &R  ) ;
int Jump (string idxReg1 , string MemAddress, Register &R , string & PC  ) ;
bool Halt () ;
    
};
#endif 