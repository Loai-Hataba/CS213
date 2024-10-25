#include "CPU.h"
#include "Regist.h"
#include "Memory.h"

int main()
{
    CPU cpu;
    Memory memory;
    Register registers(16);
    cpu.print();
    return 0;
}