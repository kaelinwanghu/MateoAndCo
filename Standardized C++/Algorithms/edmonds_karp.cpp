#include <bits/stdc++.h>
using namespace std;

/* ============================================================
   EDMONDS–KARP (MAX FLOW)
   - BFS level-by-level augmenting paths
   - O(V * E^2) worst-case; simple and reliable
   - Use int64_t capacities/flow sums
   ============================================================ */
struct ek_edge
{
    int32_t to, rev;
    int64_t cap;
};

struct edmonds_karp
{
    int32_t n = 0;
    vector<vector<ek_edge>> adj;

    edmonds_karp() = default;
    explicit edmonds_karp(int32_t n_) { init(n_); }

    void init(int32_t n_)
    {
        n = n_;
        adj.assign(n, {});
    }

    // Add directed edge u->v with capacity cap (and residual reverse edge)
    void add_edge(int32_t u, int32_t v, int64_t cap)
    {
        ek_edge a{v, (int32_t)adj[v].size(), cap};
        ek_edge b{u, (int32_t)adj[u].size(), 0};
        adj[u].push_back(a);
        adj[v].push_back(b);
    }

    // BFS to find augmenting path, storing parent (node, edge-index)
    bool bfs(int32_t s, int32_t t, vector<pair<int32_t,int32_t>>& parent) const
    {
        parent.assign(n, {-1, -1});
        queue<int32_t> q;
        q.push(s);
        parent[s] = {s, -1};
        while (!q.empty())
        {
            int32_t u = q.front(); q.pop();
            for (int32_t ei = 0; ei < (int32_t)adj[u].size(); ++ei)
            {
                const ek_edge& e = adj[u][ei];
                if (parent[e.to].first == -1 && e.cap > 0)
                {
                    parent[e.to] = {u, ei};
                    if (e.to == t) return true;
                    q.push(e.to);
                }
            }
        }
        return false;
    }

    int64_t max_flow(int32_t s, int32_t t)
    {
        int64_t flow = 0;
        vector<pair<int32_t,int32_t>> parent;
        while (bfs(s, t, parent))
        {
            // bottleneck
            int64_t aug = LLONG_MAX;
            for (int32_t v = t; v != s; )
            {
                auto [u, ei] = parent[v];
                const ek_edge& e = adj[u][ei];
                aug = min(aug, e.cap);
                v = u;
            }
            // apply
            for (int32_t v = t; v != s; )
            {
                auto [u, ei] = parent[v];
                ek_edge& e  = adj[u][ei];
                ek_edge& re = adj[e.to][e.rev];
                e.cap -= aug;
                re.cap += aug;
                v = u;
            }
            flow += aug;
        }
        return flow;
    }
};