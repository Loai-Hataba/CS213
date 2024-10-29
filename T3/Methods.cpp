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
        std::string key = "";
        key += firstDigit;
        r[key] = "00"; // Initialize the map with empty values
    }
}
int hexToDec(std :: string hex)
{
    int dec = stoi(hex, nullptr, 16);
    return dec;
}
string decToHex(int dec)
{
    if (dec == 0)
    {
        return "00";
    }

    string hexDigits = "0123456789ABCDEF";
    string hexadecimal = "";

    while (dec > 0)
    {
        int remainder = dec % 16;
        hexadecimal = hexDigits[remainder] + hexadecimal;
        dec /= 16;
    }
    if (hexadecimal.length() < 2) hexadecimal = "0" + hexadecimal;
    return hexadecimal;
}

string hexToBin(const string& hex) {
    std::string bin;
    for (char ch : hex) {
        int n = (ch >= '0' && ch <= '9') ? ch - '0' : ch - 'A' + 10;
        bin += std::bitset<4>(n).to_string();
    }
    return bin;
}

// Convert binary string to hex string
string binToHex(const string& bin) {
    int  dec = stoi(bin, nullptr,2);
    cout<<"decimal :"<<dec<<endl;
    string hex = decToHex(dec);
    return hex;
}

string GetPath()
{
    string Res;
    cout << "\nPlease Enter The Path Like This Formula --- >  C:\\Users\\YourUsername\\Documents\\example.txt" << endl;
    cout << "Please Enter The Path Of The File " << ": ";
    cin.ignore(0, '\n');
    // Use getline to capture the entire file path, including spaces and special characters
    getline(cin, Res);
    return Res;
}
string addBin(string bin1, string bin2){
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

    return res_bin;
}