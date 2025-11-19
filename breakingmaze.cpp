#include <bits/stdc++.h>
using namespace std;

array<pair<int, int>, 4> dir = {pair<int, int>(1, 0), pair<int, int>(0, -1), pair<int, int>(-1, 0), pair<int, int>(0, 1)};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, s, cell_cost;
    cin >> n >> m >> s;
    deque<tuple<int, int, int, int>> q;
    vector<vector<int>> cost(n, vector<int>(m));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> cell_cost;
            cost[i][j] = cell_cost;
        }
    }

    if (cost[0][0] > s)
    {
        cout << 0 << "\n"; return 0;
    }

    if (n == 1 && m == 1)
    {
        cout << 0 << "\n";
        return 0;
    }

    vector<vector<int>> best_cost(n, vector<int>(m, INT32_MAX));
    best_cost[0][0] = cost[0][0];
    q.emplace_back(0, 0, best_cost[0][0], 0);
    int best_path = -1;

    while (!q.empty())
    {
        auto [x, y, current_cost, current_step] = q.front();
        // cout << "x: " << x << " y: " << y << " current_cost: " << current_cost << " with step: " << current_step << "\n";
        q.pop_front();
        for (auto [dx, dy] : dir)
        {
            int new_x = x + dx;
            int new_y = y + dy;
            if (new_x < 0 || new_x >= n)
            {
                continue;
            }
            if (new_y < 0 || new_y >= m)
            {
                continue;
            }
            int potential_cost = current_cost + cost[new_x][new_y];
            if (potential_cost < best_cost[new_x][new_y] && potential_cost <= s)
            {
                best_cost[new_x][new_y] = potential_cost;
                if (new_x == n - 1 && new_y == m - 1)
                {
                    cout << current_step + 1 << "\n";
                    return 0;
                }
                q.emplace_back(new_x, new_y, potential_cost, current_step + 1);
            }
        }
    }
    cout << best_path << "\n";
}