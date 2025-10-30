#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int d, n;
    cin >> d;
    while (d--)
    {
        int total = 0;
        cin >> n;
        vector<int> nums(3 * n);
        for (int i = 0; i < 3 * n; ++i)
        {
            cin >> nums[i];
        }
        sort(nums.begin(), nums.end());
        int idx = 3 * n - 2;
        for (int i = 0; i < n; ++i)
        {
            total += nums[idx];
            idx -= 2;
        }
        cout << total << "\n";
    }
    return 0;
}