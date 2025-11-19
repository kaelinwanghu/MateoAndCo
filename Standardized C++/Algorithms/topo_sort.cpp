#include <bits/stdc++.h>
using namespace std;

vector<int32_t> topological_sort_kahn(
    int32_t n,
    const vector<vector<int32_t>>& adj // directed edges u -> v
)
{
    vector<int32_t> indeg(n, 0);
    for (int32_t u = 0; u < n; ++u)
        for (int32_t v : adj[u]) ++indeg[v];

    queue<int32_t> q;
    for (int32_t i = 0; i < n; ++i) if (indeg[i] == 0) q.push(i);

    vector<int32_t> order;
    order.reserve(n);

    while (!q.empty())
    {
        int32_t u = q.front(); q.pop();
        order.push_back(u);
        for (int32_t v : adj[u])
        {
            if (--indeg[v] == 0) q.push(v);
        }
    }

    // If order.size() < n, there was a cycle (no valid topological order)
    return order;
}