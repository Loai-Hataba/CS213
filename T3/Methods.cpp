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
}}
}
int stringToInt(const string &str)
{
    int Temp = 0;
    bool isNegative = false;
    size_t i = 0;

    // Check for a negative sign
    if (str[0] == '-')
    {
        isNegative = true;
        i = 1; // Start conversion from the next character
    }

    // Convert each character to its numeric value
    for (; i < str.size(); ++i)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            Temp = Temp * 10 + (str[i] - '0');
        }
        else
        {
            cout << "Invalid input: non-numeric character found!" << endl;
            return 0; // or handle error as needed
        }
    }

    return isNegative ? -Temp : Temp;
}
