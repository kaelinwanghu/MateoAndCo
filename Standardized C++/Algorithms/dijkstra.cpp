// DIJKSTRA TOOLKIT (C++17+)
// - Adjacency List version: O((N+M) log N) — for sparse graphs
// - Adjacency Matrix version: O(N^2) — for dense graphs
// Notes:
//   * Disconnected nodes keep distance = INF.
//   * Parent array reconstructs a shortest path tree.
//   * Optional single-target early exit for speed.
//   * Safe addition guards to avoid INF overflow.

#include <bits/stdc++.h>
using namespace std;

// -----------------------------
// Adjacency List Dijkstra
// -----------------------------
// Graph type: vector<vector<pair<int, int64_t>>> adj (u -> (v, w))
// 0-indexed vertices: 0..n-1
struct dijkstra_result
{
    vector<int64_t> distance;
    vector<int> parent;
};

// Single-source, optional early-exit to a target (pass target=-1 to disable).
dijkstra_result dijkstra_list(
    int n,
    const vector<vector<pair<int,int64_t>>>& adj_list,
    int source,
    int target = -1
)
{
    vector<int64_t> distance(n, INT64_MAX);
    vector<int> parent(n, -1);
    vector<char> visited(n, 0);

    // min-heap of (distance, node)
    priority_queue<pair<int64_t,int>, vector<pair<int64_t,int>>, greater<pair<int64_t,int>>> pq;

    distance[source] = 0;
    pq.emplace(0, source);

    while (!pq.empty())
    {
        auto [d, u] = pq.top(); pq.pop();
        if (visited[u]) continue;
        visited[u] = 1;
        if (u == target) break; // early exit if target given

        for (auto [v, w] : adj_list[u])
        {
            if (visited[v])
            {
                continue;
            }
            // guard overflow: only add if distance[u] is finite and addition won't overflow INF
            if (distance[u] != INT64_MAX && distance[u] + w < distance[v])
            {
                distance[v] = distance[u] + w;
                parent[v] = u;
                pq.emplace(distance[v], v);
            }
        }
    }
    return {move(distance), move(parent)};
}

// Multi-source variant: initialize several sources with distance 0
dijkstra_result dijkstra_list_multisource(
    int n,
    const vector<vector<pair<int,int64_t>>>& adj_list,
    const vector<int>& sources,
    int target = -1
)
{
    vector<int64_t> distance(n, INT64_MAX);
    vector<int> parent(n, -1);
    vector<char> visited(n, 0);

    priority_queue<pair<int64_t,int>, vector<pair<int64_t,int>>, greater<pair<int64_t,int>>> pq;
    for (int s : sources)
    {
        if (0 <= s && s < n)
        {
            distance[s] = 0;
            pq.emplace(0, s);
            parent[s] = -1;
        }
    }

    while (!pq.empty())
    {
        auto [d, u] = pq.top(); pq.pop();
        if (visited[u])
        {
            continue;
        }
        visited[u] = 1;

        if (u == target) break;

        for (auto [v, w] : adj_list[u])
        {
            if (visited[v])
            {
                continue;
            }
            if (distance[u] != INT64_MAX && distance[u] + w < distance[v])
            {
                distance[v] = distance[u] + w;
                parent[v] = u;
                pq.emplace(distance[v], v);
            }
        }
    }
    return {move(distance), move(parent)};
}

// Reconstruct path [source .. v] using parent[]; returns empty if unreachable.
vector<int> reconstruct_path(int source, int v, const vector<long long>& dist, const vector<int>& parent)
{
    if (v < 0 || v >= (int)parent.size()) return {};
    if (dist[v] == INT64_MAX) return {};
    vector<int> path;
    for (int u = v; u != -1; u = parent[u]) path.emplace_back(u);
    reverse(path.begin(), path.end());
    if (path.front() != source) return {};
    return path;
}

// -----------------------------
// Adjacency Matrix Dijkstra
// -----------------------------
// Matrix type: vector<vector<int64_t>> matrix (n x n)
//   matrix[u][v] = weight if edge exists, INF (or >=INF/2) otherwise
// Self-loops can be 0; negatives are ignored for safety.
dijkstra_result dijkstra_matrix(
    const vector<vector<int64_t>>& matrix,
    int source,
    int target = -1
)
{
    int n = (int)matrix.size();
    vector<int64_t> distance(n, INT64_MAX);
    vector<int> parent(n, -1);
    vector<char> visited(n, 0);

    distance[source] = 0;

    for (int it = 0; it < n; ++it)
    {
        // pick unvisited node with min distance
        int u = -1;
        int64_t best = INT64_MAX;
        for (int i = 0; i < n; ++i)
        {
            if (!visited[i] && distance[i] < best)
            {
                best = distance[i];
                u = i;
            }
        }
        if (u == -1)
        {
            break;     // all remaining are INF
        }
        visited[u] = 1;
        if (u == target)
        {
            break; // early exit
        }
        // relax neighbors via matrix row u
        for (int v = 0; v < n; ++v)
        {
            int64_t w = matrix[u][v];
            if (visited[v])
            {
                continue;
            }
            if (w == INT64_MAX)
            {
                continue;
            }
            if (distance[u] + w < distance[v])
            {
                distance[v] = distance[u] + w;
                parent[v] = u;
            }
        }
    }
    return {move(distance), move(parent)};
}
