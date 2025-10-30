#include <bits/stdc++.h>
using namespace std;

inline int64_t get_power(int64_t n, int64_t m)
{
    for (int i = 0; i < n; ++i)
    {
        m = (2 * m) / 3;
    }
    return m;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int64_t n, m;
    cin >> n >> m;
    vector<int64_t> foods(n);
    vector<vector<vector<int64_t>>> dp(n + 1, vector<vector<int64_t>>(n + 1, vector<int64_t>(n + 1, INT32_MIN)));
    for (int64_t i = 0; i < n; ++i)
    {
        cin >> foods[i];
    }
    dp[0][0][0] = 0;
    for (int64_t i = 0; i < n; ++i)
    {
        for (int64_t j = 0; j < n + 1; ++j)
        {
            for (int64_t k = 0; k < n + 1; ++k)
            {
                int64_t no_eat = dp[i][j][k];
                if (no_eat == INT32_MIN || k == n)
                {
                    continue;
                }
                if (j == 0)
                {
                    dp[i + 1][0][k + 1] = max(dp[i + 1][0][k + 1], no_eat);
                }
                else if (j != 0)
                {
                    dp[i + 1][j - 1][k + 1] = max(dp[i + 1][j - 1][k + 1], no_eat);
                }
                
                if (j != n)
                {
                    int64_t yes_eat = 0;
                    if (k >= 2)
                    {
                        yes_eat = no_eat + min(m, foods[i]);
                    }
                    else
                    {
                        yes_eat = no_eat + min((get_power(k, m)), foods[i]);
                    }
                    dp[i + 1][j + 1][0] = max(dp[i + 1][j + 1][0], yes_eat);
                }
            }
        }
    }
    int64_t max_food = 0;
    for (int64_t i = 0; i < n + 1; ++i)
    {
        for (int64_t j = 0; j < n + 1; ++i)
        {
            if (dp[n][i][j] > max_food)
            {
                max_food = dp[n][i][j];
            }
        }
    }
    cout << max_food << "\n";
    return 0;
}