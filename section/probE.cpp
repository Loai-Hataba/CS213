#include <iostream>
#include <vector>
using namespace std;
#define el endl

int main()
{
    int n, q;
    cin >> n >> q;
    vector<long long> a(n), sums(n);
    vector<int> output(q);

    cin >> a[0];
    sums[0] = a[0];
    for (int i = 1; i < n; ++i)
    {
        cin >> a[i];
        sums[i] = sums[i - 1] + a[i];
    }

    for (int i = 0; i < q; i++)
    {
        long long x;
        cin >> x;

        if (sums[n - 1] <= x)
        {
            output[i] = -1;
            continue;
        }

        int low = 0, high = n - 1;
        int ans = -1;

        while (low <= high)
        {
            int mid = low + (high - low) / 2;

            if (sums[mid] > x)
            {
                ans = mid;
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }

        output[i] = ans + 1;
    }

    for (int ans : output)
    {
        cout << ans << el;
    }

    return 0;
}
