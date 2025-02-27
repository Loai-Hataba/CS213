#include <iostream>

using namespace std;

long probB(int k);
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int a, b;
        cin >> a >> b;
        cout << probB(a - b) + probB(a + b) << el;
    }
}

long probB(int k)
{
    if (k == 1)
        return 1;
    else if (k == 0)
        return 1;
    long a = 1, b = 1;
    long results = 0;
    for (int i = 2; i <= k; ++i)
    {
        results = a + b;
        a = b;
        b = results;
    }
    return results;
}
