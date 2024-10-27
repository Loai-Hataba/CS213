#include "CU.h"
// Control Unit --> CU

void CU::Load(string idxReg, string MemAddress, Register &R, Memory &M)
{
    R.setCell(idxReg, M.getCell(MemAddress));
}

void CU::Load(string idxReg, string value, Register &R)
{
    R.setCell(idxReg, value);
}

void CU::Store(string idxReg, string MemAddress, Register &R, Memory &M)
{
    M.setCell(MemAddress, R.getCell(idxReg));
}

void CU::Move(string idxReg1, string idxReg2, Register &R)
{
    R.setCell(idxReg2, R.getCell(idxReg1));
}

void CU::Jump(string idxReg, string MemAddress, Register &R, string &PC)
{

    if (R.getCell(0) == R.getCell(idxReg))
    {
        PC = MemAddress ; 
    } 
}

void CU::Halt()
{
    exit(0); // Properly terminate the program
}
