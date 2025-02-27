#include <iostream>
using namespace std;
#define el endl

bool IsPalindrome(string string);
int PalindromeCount(int i, string current);

string word;
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        cin >> word;
        cout << PalindromeCount(0, "") << el;
    }
}

int PalindromeCount(int k, string current)
{
    if (k >= word.size())
    {
        if (IsPalindrome(current) && current.size() > 1)
            return true;
        return false;
    }
    string tmp = current;
    tmp += word[k];
    return PalindromeCount(k + 1, tmp) + PalindromeCount(k + 1, current);
}

bool IsPalindrome(string string)
{
    int length = string.size();
    for (int i = 0; i < length / 2; i++)
    {
        if (string[i] != string[length - i - 1])
        {
            return false;
        }
    }
    return true;
}