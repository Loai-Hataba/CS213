#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>
using namespace std;
int main()
{
    int n, q;
    cin >> n >> q;
    vector<int> vecc(n);

    unordered_map<int, set<int>> indexed;

    int current_minimum = INT_MAX, current_maxumum = INT_MIN;
    for (int i = 0; i < n; ++i)
    {
        cin >> vecc[i];
        indexed[vecc[i]].insert(i);
        current_minimum = min(current_minimum, vecc[i]);
        current_maxumum = max(current_maxumum, vecc[i]);
    }

    while (q--)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int x, y;
            cin >> y >> x;
            int old = vecc[--y];
            indexed[old].erase(y);
            if (indexed[old].empty())
            {
                indexed.erase(old);
                if (old == current_minimum || old == current_maxumum)
                {

                    current_minimum = INT_MAX;
                    current_maxumum = INT_MIN;
                    for (auto &Pair : indexed)
                    {
                        current_minimum = min(current_minimum, Pair.first);
                        current_maxumum = max(current_maxumum, Pair.first);
                    }
                }
            }

            vecc[y] = x;
            indexed[x].insert(y);
            current_minimum = min(current_minimum, x);
            current_maxumum = max(current_maxumum, x);
        }

        if (t == 2)
        {
            int x;
            cin >> x;
            if (indexed.find(x) != indexed.end())
            {
                cout << (*indexed[x].begin() + 1) << endl;
            }
            else
            {
                cout << -1 << endl;
            }
        }
        if (t == 3)
        {
            cout << current_minimum << endl;
        }
        if (t == 4)
        {
            cout << current_maxumum << endl;
        }
    }
    return 0;
}