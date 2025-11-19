// BELLMAN-FORD TOOLKIT (C++17+)
// - Handles negative weights (no negative cycles on valid shortest paths).
// - O(N * M), early-stops if an iteration makes no updates.
// - Detects reachable negative cycles and marks all vertices reachable from them.
// - Multi-source variant provided.
//
// Graph representations supported:
//   1) Edge list: vector<tuple<int,int,int64_t>> edges  (u, v, w)
//   2) Adjacency list wrapper: vector<vector<pair<int,int64_t>>> adj_list (u -> (v, w))
//
// Conventions:
//   * Unreachable: distance[v] = INT64_MAX
//   * parent[v] reconstructs a shortest-path tree (undefined for nodes affected by neg cycles)
//   * in_negative_cycle[v] = 1 if v is reachable from some reachable negative cycle

#include <bits/stdc++.h>
using namespace std;

struct bellman_ford_result
{
    vector<int64_t> distance;
    vector<int> parent;
    vector<char> in_negative_cycle; // 1 if v is reachable from a reachable negative cycle
    bool has_negative_cycle;
};

// -----------------------------
// Internal helpers
// -----------------------------
namespace bf_detail {

inline bool relax_all_once(
    const vector<tuple<int,int,int64_t>>& edges,
    vector<int64_t>& distance,
    vector<int>& parent
)
{
    bool updated = false;
    for (auto [u, v, w] : edges)
    {
        if (distance[u] != INT64_MAX && distance[u] + w < distance[v])
        {
            distance[v] = distance[u] + w;
            parent[v] = u;
            updated = true;
        }
    }
    return updated;
}

// Mark everything reachable (via forward edges) from any vertex that can still relax after n-1 iters.
inline void mark_negative_cycle_region(
    int n,
    const vector<tuple<int,int,int64_t>>& edges,
    const vector<int64_t>& distance,
    vector<char>& in_negative_cycle
)
{
    vector<vector<int>> forward_adj(n);
    forward_adj.reserve(n);
    for (auto [u, v, w] : edges) forward_adj[u].push_back(v);

    queue<int> q;
    vector<char> pushed(n, 0);

    // Seed with vertices that would still relax on iteration n (reachable neg cycles)
    for (auto [u, v, w] : edges)
    {
        if (distance[u] != INT64_MAX && distance[u] + w < distance[v])
        {
            if (!pushed[v])
            {
                pushed[v] = 1;
                in_negative_cycle[v] = 1;
                q.push(v);
            }
        }
    }

    // Propagate forward: anything reachable from these is also affected
    while (!q.empty())
    {
        int x = q.front(); q.pop();
        for (int y : forward_adj[x])
        {
            if (!in_negative_cycle[y])
            {
                in_negative_cycle[y] = 1;
                if (!pushed[y])
                {
                    pushed[y] = 1;
                    q.push(y);
                }
            }
        }
    }
}

} // namespace bf_detail

// -----------------------------
// Core: Bellman–Ford on edge list (single-source)
// -----------------------------
bellman_ford_result bellman_ford_edges(
    int n,
    const vector<tuple<int,int,int64_t>>& edges,
    int source
)
{
    vector<int64_t> distance(n, INT64_MAX);
    vector<int> parent(n, -1);
    vector<char> in_negative_cycle(n, 0);

    distance[source] = 0;

    for (int it = 0; it < n - 1; ++it)
    {
        bool updated = bf_detail::relax_all_once(edges, distance, parent);
        if (!updated) break;
    }

    bool has_negative_cycle = false;
    for (auto [u, v, w] : edges)
    {
        if (distance[u] != INT64_MAX && distance[u] + w < distance[v])
        {
            has_negative_cycle = true;
            break;
        }
    }
    if (has_negative_cycle)
    {
        bf_detail::mark_negative_cycle_region(n, edges, distance, in_negative_cycle);
    }

    return {move(distance), move(parent), move(in_negative_cycle), has_negative_cycle};
}

// -----------------------------
// Core: Bellman–Ford on edge list (multi-source)
// -----------------------------
bellman_ford_result bellman_ford_edges_multisource(
    int n,
    const vector<tuple<int,int,int64_t>>& edges,
    const vector<int>& sources
)
{
    vector<int64_t> distance(n, INT64_MAX);
    vector<int> parent(n, -1);
    vector<char> in_negative_cycle(n, 0);

    for (int s : sources)
    {
        if (0 <= s && s < n)
        {
            distance[s] = 0;
            parent[s] = -1;
        }
    }

    for (int it = 0; it < n - 1; ++it)
    {
        bool updated = bf_detail::relax_all_once(edges, distance, parent);
        if (!updated) break;
    }

    bool has_negative_cycle = false;
    for (auto [u, v, w] : edges)
    {
        if (distance[u] != INT64_MAX && distance[u] + w < distance[v])
        {
            has_negative_cycle = true;
            break;
        }
    }
    if (has_negative_cycle)
    {
        bf_detail::mark_negative_cycle_region(n, edges, distance, in_negative_cycle);
    }

    return {move(distance), move(parent), move(in_negative_cycle), has_negative_cycle};
}

// -----------------------------
// Adjacency list wrappers
// -----------------------------
bellman_ford_result bellman_ford_list(
    int n,
    const vector<vector<pair<int,int64_t>>>& adj_list,
    int source
)
{
    vector<tuple<int,int,int64_t>> edges;
    edges.reserve([&](){
        size_t m = 0;
        for (const auto& nbrs : adj_list) m += nbrs.size();
        return m;
    }());
    for (int u = 0; u < n; ++u)
        for (auto [v, w] : adj_list[u])
            edges.emplace_back(u, v, w);

    return bellman_ford_edges(n, edges, source);
}

bellman_ford_result bellman_ford_list_multisource(
    int n,
    const vector<vector<pair<int,int64_t>>>& adj_list,
    const vector<int>& sources
)
{
    vector<tuple<int,int,int64_t>> edges;
    edges.reserve([&](){
        size_t m = 0;
        for (const auto& nbrs : adj_list) m += nbrs.size();
        return m;
    }());
    for (int u = 0; u < n; ++u)
        for (auto [v, w] : adj_list[u])
            edges.emplace_back(u, v, w);

    return bellman_ford_edges_multisource(n, edges, sources);
}

// -----------------------------
// Path reconstruction (reuse your existing helper):
// vector<int> reconstruct_path(int source, int v, const vector<long long>& dist, const vector<int>& parent);
//
// Note: for nodes with in_negative_cycle[v] = 1, shortest paths are undefined.
// -----------------------------
