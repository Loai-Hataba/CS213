#include "Methods.h"
bool IsPowerOf2(int num)
{
    if (num <= 0)
        cout << "Error : Invalid Size !!" << endl;
    while (num % 2 == 0)
    {
        num = num / 2;
    }
    return (num == 1);
}