#include <iostream>
#include <unordered_map>
using namespace std;
#define el endl
int main()
{
    int n, q;
    cin >> n >> q;
    int a[n];
    unordered_map<int, int> map;
    for (int i = 0; i < n; i++)
    {
        int t;
        cin >> t;
        map[t]++;
        a[i] = t;
    }
    int res[q];
    for (int i = 0; i < q; i++)
    {
        int t;
        cin >> t;
        res[i] = t;
    }
    for (auto k : res)
    {
        cout << map[k] << el;
    }
}