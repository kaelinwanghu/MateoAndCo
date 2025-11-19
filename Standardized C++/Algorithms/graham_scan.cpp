// GRAHAM'S SCAN CONVEX HULL (C++17+)
// - O(N log N): sort by polar angle around pivot, then stack
// - Works with integer coordinates (int64_t)
// - Returns hull in CCW order, starting at the pivot (lowest y, then lowest x)
// - Option: include_collinear_on_hull = true keeps collinear boundary points;
//           false collapses collinear runs to endpoints (typical for ICPC).
//
// Input format:
//   vector<pair<int64_t,int64_t>> points = {{x0,y0}, {x1,y1}, ...};
// Output:
//   convex_hull_result with hull indices (referring to original points) and hull points.
//
// Notes:
//   * Duplicates are removed before processing.
//   * For N <= 2, the hull is just the distinct points given.
//   * No overflow gymnastics; standard cross/dist2 with int64_t.

#include <bits/stdc++.h>
using namespace std;

struct convex_hull_result
{
    vector<int> hull_indices;                       // indices into original input
    vector<pair<int64_t,int64_t>> hull_points;  // points in CCW order
};

namespace graham_detail {

struct point
{
    int64_t x, y;
    int original_index;
};

inline int64_t cross(const point& a, const point& b, const point& c)
{
    // cross(AB, AC) = (b - a) x (c - a)
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

inline int64_t squared_distance(const point& a, const point& b)
{
    int64_t dx = a.x - b.x;
    int64_t dy = a.y - b.y;
    return dx * dx + dy * dy;
}

// Remove exact duplicates; keep the first occurrence's original index.
inline vector<point> deduplicate(const vector<pair<int64_t,int64_t>>& pts)
{
    vector<point> unique_pts;
    unique_pts.reserve(pts.size());
    unordered_map<int64_t, unordered_map<int64_t, int>> seen; // y->(x->index), to avoid building a custom hash

    for (int i = 0; i < (int)pts.size(); ++i)
    {
        int64_t x = pts[i].first, y = pts[i].second;
        auto& row = seen[y];
        if (row.find(x) == row.end())
        {
            row[x] = i;
            unique_pts.push_back({x, y, i});
        }
    }
    return unique_pts;
}

} // namespace graham_detail

// Graham's Scan main routine.
// include_collinear_on_hull = false -> typical competitive setting (no interior collinear points on edges)
// include_collinear_on_hull = true  -> keeps all collinear boundary points along edges
convex_hull_result graham_scan_convex_hull(
    const vector<pair<int64_t,int64_t>>& input_points,
    bool include_collinear_on_hull = false
)
{
    using namespace graham_detail;

    vector<point> points = deduplicate(input_points);
    const int n = (int)points.size();

    convex_hull_result result;

    if (n == 0)
    {
        return result;
    }
    if (n == 1)
    {
        result.hull_indices = { points[0].original_index };
        result.hull_points  = { {points[0].x, points[0].y} };
        return result;
    }
    if (n == 2)
    {
        // Keep the two distinct points (sorted CCW by Graham pivot logic below)
        int a = 0, b = 1;
        // Choose pivot as lowest y then lowest x
        if (points[b].y < points[a].y || (points[b].y == points[a].y && points[b].x < points[a].x))
            swap(a, b);
        result.hull_indices = { points[a].original_index, points[b].original_index };
        result.hull_points  = { {points[a].x, points[a].y}, {points[b].x, points[b].y} };
        return result;
    }

    // 1) Find pivot: lowest y, then lowest x
    int pivot_idx = 0;
    for (int i = 1; i < n; ++i)
    {
        if (points[i].y < points[pivot_idx].y ||
            (points[i].y == points[pivot_idx].y && points[i].x < points[pivot_idx].x))
        {
            pivot_idx = i;
        }
    }
    swap(points[0], points[pivot_idx]);
    const point pivot = points[0];

    // 2) Sort remaining points by polar angle w.r.t. pivot (counterclockwise)
    //    Break ties (collinear with pivot) by distance from pivot (nearer first).
    sort(points.begin() + 1, points.end(), [&](const point& a, const point& b)
    {
        int64_t cr = cross(pivot, a, b);
        if (cr != 0) return cr > 0; // a before b if pivot->a is CCW of pivot->b
        int64_t da = squared_distance(pivot, a);
        int64_t db = squared_distance(pivot, b);
        return da < db;             // closer first on the same ray
    });

    // If we want to include collinear boundary points, we need the farthest point
    // for each angle to appear *last* among its collinear group; the sort put nearer first,
    // which is OK; we just change the pop condition below to < 0 (strict right turn only).
    // If we want to exclude interior collinear points, we will pop on <= 0.

    // 3) Build the hull using a stack
    vector<point> hull_stack;
    hull_stack.reserve(n);

    hull_stack.push_back(points[0]);
    hull_stack.push_back(points[1]);

    auto should_pop = [&](const point& a, const point& b, const point& c)
    {
        int64_t cr = cross(a, b, c);
        if (include_collinear_on_hull)
            return cr < 0;    // only pop on right turn; keep collinear
        else
            return cr <= 0;   // pop on right turn or collinear (removes interior collinears)
    };

    for (int i = 2; i < n; ++i)
    {
        while ((int)hull_stack.size() >= 2 &&
               should_pop(hull_stack[(int)hull_stack.size() - 2],
                          hull_stack[(int)hull_stack.size() - 1],
                          points[i]))
        {
            hull_stack.pop_back();
        }
        hull_stack.push_back(points[i]);
    }

    // Edge case: if all points are collinear and include_collinear_on_hull == false,
    // the above will leave only two endpoints (good).
    // If include_collinear_on_hull == true, we keep the whole collinear chain.

    // 4) Emit result (indices + points), in CCW order starting from pivot
    result.hull_indices.reserve(hull_stack.size());
    result.hull_points.reserve(hull_stack.size());
    for (const auto& p : hull_stack)
    {
        result.hull_indices.push_back(p.original_index);
        result.hull_points.emplace_back(p.x, p.y);
    }

    return result;
}
