#include <iostream>
#include <cmath>
using namespace std;

int GCD(int x, int y)
{
    return ((x / y == 0) ? 0 : (x % y == 0) ? y
                                            : GCD(y, (x % y)));
}

double power(double x, int pow)
{
    return (pow == 0) ? 1 : (pow == 1) ? x
                        : (pow < 0)    ? (1 / (power(x, (pow * -1) - 1) * x))
                                       : power(x, pow - 1) * x;
}
int main()
{
    cout << GCD(12, 8) << endl;
    cout << power(2, 4) << endl;
    cout << power(2, -4) << endl;
}