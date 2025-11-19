#include <bits/stdc++.h>
using namespace std;

#define EPS 0.1

int get_path_product(const vector<vector<int>>& adj_list, int source, int dest)
{
    int all_product_sums = 0;
    int graph_size = adj_list.size();
    deque<pair<int, int>> q; // idx and current product;
    vector<int> visited(graph_size, false);
    q.emplace_back(source, 1);
    visited[source] = true;
    while (!q.empty())
    {
        auto [node, current_product] = q.front(); q.pop_front();
        if (node == dest)
        {

        }
        for (auto v : adj_list[node])
        {
            if (visited[v]) continue;
            current_product *= adj_list[v].size();
            q.emplace_back();
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, u, v, x;
    double answer;
    cin >> n >> m;
    vector<vector<int>> adj_list(n, vector<int>());
    vector<vector<int>> back(n, vector<int>());
    for (int i = 0; i < m; ++i)
    {
        cin >> u >> v;
        adj_list[u].emplace_back(v);
        adj_list[v].emplace_back(u);
    }
    cin >> x;

    for (int i = 0; i < n; ++i)
    {
        if (i == x) continue;
        double xp = get_path_product(adj_list, x, i);
        answer += 1.0 / xp;
    }

    cout << answer << "\n";
}