#include <bits/stdc++.h>
using namespace std;

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, a, c, x0;
    cin >> n >> m >> a >> c >> x0;
    int count = 0;
    vector<int> actual(n);
    actual[0] = (a * x0 + c) % m;
    for (int i = 1; i < n; ++i)
    {
        actual[i] = (a * actual[i - 1] + c) % m;
    }
    // for (auto thing : actual)
    // {
    //     cout << " | : " << thing << "\n";
    // }
    for (int i = 0; i < n; ++i)
    {
        int to_search = actual[i];
        int high = n - 1, low = 0;
        while (high >= low)
        {
            int idx = (high + low) / 2;
            int mid_value = actual[idx];
            if (to_search > mid_value)
            {
                low = idx + 1;
            }
            else if (to_search < mid_value)
            {
                high = idx - 1;
            }
            else
            {
                ++count;
                // cout << "found: " << to_search << "\n";
                break;
            }
        }
    }
    cout << count << "\n";
    return 0;
}