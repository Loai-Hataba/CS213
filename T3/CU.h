#ifndef _CU_H
#define _CU_H
#include "Headers.h"
#include "Regist.h"
#include "Memory.h"
class CU
{
public:
void Load (int idxReg , int idxMemory , Register &R , Memory &M) ;
void Load (int idxReg , int value , Register &R ) ;
void Store (int idxReg , int idxMemory , Register &R , Memory & M ) ;
void Move (int idxReg1 , int idxReg2 , Register &R  ) ;
void Jump (int idxReg1 , int idxMemory , Register &R , int & PC  ) ;
void Halt () ;
    
};



#endif 