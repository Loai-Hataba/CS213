#include "Methods.h"

/*string decToHex(int dec) {
    if (dec == 0) {
        return "00";
    }

    string hexDigits = "0123456789ABCDEF";
    string hexadecimal = "";

    while (dec > 0) {
        int remainder = dec % 16;
        hexadecimal = hexDigits[remainder] + hexadecimal;
        dec /= 16;
    }
    if (hexadecimal.length() < 2) {
        hexadecimal = "0" + hexadecimal;
    }
    cout << "HEX: " << hexadecimal << endl;
    return hexadecimal;
}

int hexToDec(string hex){
    int dec = stoi(hex, nullptr, 16);
    cout << "DEC: " << dec << endl;
    return dec;
}*/
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

void GenerateMemory(std::map<std::string, std::string> &m)
{
    for (size_t i = 0; i < 16; ++i) // First hex digit (0 to F)
    {
        char firstDigit;
        if (i < 10)
        {
            firstDigit = '0' + i; // '0' to '9'
        }
        else
        {
            firstDigit = 'A' + (i - 10); // 'A' to 'F'
        }

        for (size_t j = 0; j < 16; ++j) // Second hex digit (0 to F)
        {
            char secondDigit;
            if (j < 10)
            {
                secondDigit = '0' + j; // '0' to '9'
            }
            else
            {
                secondDigit = 'A' + (j - 10); // 'A' to 'F'
            }

            std::string key = std::string(1, firstDigit) + secondDigit;
            m[key] = "00"; // Initialize the map with "00"
        }
    }
}

void GenerateRegister(map<string, string> &r)
{
    for (size_t i = 0; i < 16; ++i) // First hex digit (0 to F)
    {
        char firstDigit;
        if (i < 10)
        {
            firstDigit = '0' + i; // '0' to '9'
        }
        else
        {
            firstDigit = 'A' + (i - 10); // 'A' to 'F'
        }
        std::string key;
        key += firstDigit;
        r[key] = "00"; // Initialize the map with empty values
    }
}
int hexToDec(std :: string hex)
{
    int dec = stoi(hex, nullptr, 16);
    cout << "DEC: " << dec << endl;
    return dec;
}
string decToHex( int dec)
{
    if (dec == 0)
    {
        return "0";
    }

    string hexDigits = "0123456789ABCDEF";
    string hexadecimal = "";

    while (dec > 0)
    {
        int remainder = dec % 16;
        hexadecimal = hexDigits[remainder] + hexadecimal;
        dec /= 16;
    }
    cout << "HEX: " << hexadecimal << endl;
    return hexadecimal;
}