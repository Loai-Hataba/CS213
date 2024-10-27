#include "CU.h"
// Control Unit --> CU

void CU::Load(int idxReg, int idxMemory, Register &R, Memory &M)
{
    if (idxMemory < 0 || idxMemory >= M.GetSize() || idxReg < 0 || idxReg >= R.GetSize())
    {
        cout << "Error: Invalid index for Load operation." <<  endl;
        return ; 
    }
        cout << "Error: Invalid index for Load  1 operation." << endl;
        return;
     }

    try
    {
        // Convert the string from memory to an integer
        int Temp =  stoi(M.getCell(idxMemory));
        int Temp = stringToInt(M.getCell(idxMemory));
        R.setCell(idxReg, Temp);
    }
    catch (const  invalid_argument &)
    {
        cout << "Error: Invalid string conversion to int." <<  endl;
    }
    catch (const  out_of_range &)
    {
        cout << "Error: Integer value out of range." <<  endl;
    }
}

void CU::Load(int idxReg, int value, Register &R)
{
    if (idxReg < 0 || idxReg >= R.GetSize())
    {
        cout << "Error: Invalid register index." <<  endl;
        return ;
    }
    R.setCell(idxReg, value);
}

void CU::Store(int idxReg, int idxMemory, Register &R, Memory &M)
{
    if (idxReg < 0 || idxReg >= R.GetSize() || idxMemory < 0 || idxMemory >= M.GetSize())
    {
        cout << "Error: Invalid index for Store operation." <<  endl;
        return ;
    }

    // Convert the register value to a string
    string Temp =  to_string(R.getCell(idxReg));
    M.setCell(idxMemory, Temp);
}

void CU::Move(int idxReg1, int idxReg2, Register &R)
{
    if (idxReg1 < 0 || idxReg1 >= R.GetSize() || idxReg2 < 0 || idxReg2 >= R.GetSize())
    {
        cout << "Error: Invalid register index for Move operation." <<  endl;
        return ;
    }
    R.setCell(idxReg2, R.getCell(idxReg1));
    cout << "R2 "<< R.getCell(idxReg2)  <<endl; 
    cout << "R1 "<< R.getCell(idxReg1)  <<endl; 
}

void CU::Jump(int idxReg, int idxMemory, Register &R, int &PC)
{
    if (idxReg < 0 || idxReg >= R.GetSize() || idxMemory < 0 )
    {
        cout << "Error: Invalid index for Jump operation." <<  endl;
        return ; 
    }

    if (R.getCell(0) == R.getCell(idxReg))
    {
        PC = idxMemory;
    }
}

void CU::Halt()
{
    exit(0); // Properly terminate the program
}
