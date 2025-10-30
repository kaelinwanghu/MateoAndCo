#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int64_t n;
    cin >> n;
    vector<int64_t> beasts(n + 1);
    vector<int64_t> dp(n + 1, 0);
    for (int64_t i = 0; i < n; ++i)
    {
        cin >> beasts[i + 1];
    }
    sort(beasts.begin() + 1, beasts.end(), greater<int64_t>());
    dp[1] = 1;
    int64_t current_coalition = beasts[1];
    pair<int64_t, int64_t> opposition = {0, 0};
    for (int64_t i = 2; i <= n; ++i)
    {
        opposition.first += beasts[i];
        opposition.second += 1;
        if (opposition.first >= current_coalition)
        {
            current_coalition += opposition.first;
            dp[i] = dp[i - 1] + opposition.second;
            opposition = {0, 0};
        }
        else
        {
            dp[i] = dp[i - 1];
        }
    }
    cout << dp[n] << "\n";
    return 0;
}