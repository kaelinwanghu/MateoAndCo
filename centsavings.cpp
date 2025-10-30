#include <bits/stdc++.h>
using namespace std;

int rounder(int n)
{
    int remainder = n % 10;
    if (remainder < 5)
    {
        return -remainder;
    }
    else
    {
        return 10 - remainder;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, d;
    cin >> n >> d;
    vector<int> products(n);
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(d + 1, vector<int>(10, INT32_MAX)));
    vector<int> cuts;
    int total = 0;
    int actual = 0;
    int group = 0;
    for (int i = 0; i < n; ++i)
    {
        cin >> products[i];
        total += products[i];
    }
    dp[0][0][0] = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j <= d; ++j)
        {
            for (int k = 0; k < 10; ++k)
            {
                int current = dp[i][j][k];
                if (current == INT32_MAX)
                {
                    continue;
                }
                int do_add = (k + products[i]) % 10;
                dp[i + 1][j][do_add] = min(dp[i + 1][j][do_add], current);
                if (j < d)
                {
                    dp[i + 1][j + 1][0] = min(dp[i + 1][j + 1][0], current + rounder(do_add));
                }
            }
        }
    }
    int true_min = INT32_MAX;
    for (int i = 0; i <= d; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            cout << "i: " << i << " and j: " << j << " | "<< dp[n][i][j] << "\n";
            if (dp[n][i][j] == INT32_MAX)
            {
                continue;
            }
            else
            {
                true_min = min(true_min, dp[n][i][j]);
            }
        }
    }
    cout << total + true_min << "\n";
    return 0;
}