// FLOYD–WARSHALL TOOLKIT (C++17+)
// - All-pairs shortest paths on adjacency matrix
// - Handles negative edges; detects negative cycles
// - O(N^3); path reconstruction via `next_vertex` matrix
// - Flags pairs (i, j) whose shortest path is affected by a reachable negative cycle
//
// Matrix convention:
//   * matrix[u][v] = edge weight if edge exists; INT64_MAX (INF) otherwise
//   * matrix[u][u] should be 0 (we'll enforce it if it’s INF)
//   * Works for directed graphs. For undirected, set both (u, v) and (v, u).
//
// Notes:
//   * If distance[i][j] == INT64_MAX => j unreachable from i
//   * If neg_cycle_on_path[i][j] == 1 => shortest path i->j is undefined (-∞)

#include <bits/stdc++.h>
using namespace std;

struct floyd_warshall_result
{
    vector<vector<int64_t>> distance;          // APSP distances
    vector<vector<int>> next_vertex;           // for path reconstruction: next_vertex[u][v] = next hop from u toward v, or -1
    vector<vector<char>> neg_cycle_on_path;    // 1 if any shortest path i->j can traverse a reachable negative cycle
    bool has_negative_cycle;                   // true if any dist[k][k] < 0
};

// Core Floyd–Warshall on a matrix
floyd_warshall_result floyd_warshall_matrix(vector<vector<int64_t>> matrix)
{
    const int n = (int)matrix.size();
    vector<vector<int64_t>> distance = matrix;
    vector<vector<int>> next_vertex(n, vector<int>(n, -1));

    // Normalize diagonal and initialize next hops
    for (int i = 0; i < n; ++i)
    {
        if (distance[i][i] == INT64_MAX) distance[i][i] = 0;
        for (int j = 0; j < n; ++j)
        {
            if (i != j && distance[i][j] != INT64_MAX)
                next_vertex[i][j] = j;
        }
    }

    // Main triple loop
    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            if (distance[i][k] == INT64_MAX) continue;
            for (int j = 0; j < n; ++j)
            {
                if (distance[k][j] == INT64_MAX) continue;
                int64_t through_k = distance[i][k] + distance[k][j];
                if (through_k < distance[i][j])
                {
                    distance[i][j] = through_k;
                    next_vertex[i][j] = next_vertex[i][k]; // first hop on i->k becomes first hop on i->j
                }
            }
        }
    }

    // Detect negative cycles: dist[v][v] < 0
    bool has_negative_cycle = false;
    for (int v = 0; v < n; ++v)
        if (distance[v][v] < 0) { has_negative_cycle = true; break; }

    // Mark pairs whose shortest path can go through any reachable negative cycle.
    // If distance[i][k] and distance[k][j] are finite for some k with distance[k][k] < 0,
    // then i->j can be improved indefinitely => undefined (-∞).
    vector<vector<char>> neg_cycle_on_path(n, vector<char>(n, 0));
    if (has_negative_cycle)
    {
        for (int k = 0; k < n; ++k)
        {
            if (distance[k][k] < 0)
            {
                for (int i = 0; i < n; ++i)
                {
                    if (distance[i][k] == INT64_MAX) continue;
                    for (int j = 0; j < n; ++j)
                    {
                        if (distance[k][j] == INT64_MAX) continue;
                        neg_cycle_on_path[i][j] = 1;
                    }
                }
            }
        }
    }

    return { move(distance), move(next_vertex), move(neg_cycle_on_path), has_negative_cycle };
}

// Reconstruct path i -> j using next_vertex; returns empty if unreachable or undefined.
// If neg_cycle_on_path[i][j] == 1, the shortest path is undefined; we return empty.
vector<int> reconstruct_path_fw(
    int source,
    int target,
    const vector<vector<int64_t>>& distance,
    const vector<vector<int>>& next_vertex,
    const vector<vector<char>>& neg_cycle_on_path
)
{
    if (source < 0 || target < 0) return {};
    if (source >= (int)next_vertex.size() || target >= (int)next_vertex.size()) return {};
    if (neg_cycle_on_path[source][target]) return {};           // undefined shortest path (-∞)
    if (distance[source][target] == INT64_MAX) return {};       // unreachable

    vector<int> path{source};
    int u = source;
    while (u != target)
    {
        u = next_vertex[u][target];
        if (u == -1) { path.clear(); return path; }             // safety: inconsistent next matrix
        path.push_back(u);
        if ((int)path.size() > (int)next_vertex.size() + 5) {   // safety guard for cycles in next
            path.clear(); return path;
        }
    }
    return path;
}

// Convenience: build matrix from edge list (directed), then run Floyd–Warshall.
// n: number of vertices [0..n-1], edges: (u, v, w). If multiple edges, keeps the lightest.
floyd_warshall_result floyd_warshall_from_edges(
    int n,
    const vector<tuple<int,int,int64_t>>& edges
)
{
    const int64_t INF = INT64_MAX;
    vector<vector<int64_t>> matrix(n, vector<int64_t>(n, INF));
    for (int i = 0; i < n; ++i) matrix[i][i] = 0;

    for (auto [u, v, w] : edges)
    {
        if (u < 0 || v < 0 || u >= n || v >= n) continue;
        if (w < matrix[u][v]) matrix[u][v] = w;
    }

    return floyd_warshall_matrix(move(matrix));
}
