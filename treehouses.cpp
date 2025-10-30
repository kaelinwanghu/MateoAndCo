#include <bits/stdc++.h>
using namespace std;

int32_t set_find(vector<int32_t>& v, int32_t a)
{
    deque<int32_t> d;
    int32_t front;
    while (v[a] != a)
    {
        d.emplace_front(a);
        a = v[a];
    }

    while (!d.empty())
    {
        front = d.front();
        d.pop_front();
        v[front] = a;
    }
    return a;
}

void set_union(vector<int32_t>& v, vector<int32_t>& r, const int32_t a, const int32_t b)
{
    int32_t a_root = set_find(v, a);
    int32_t b_root = set_find(v, b);
    if (a_root != b_root)
    {
        if (r[a_root] > r[b_root])
        {
            v[b_root] = a_root;
        }
        else if (r[a_root] == r[b_root])
        {
            r[a_root]++;
            v[b_root] = a_root;
        }
        else
        {
            v[a_root] = b_root;
        }
    }
}

bool set_query(vector<int32_t>& v, const int32_t a, const int32_t b)
{
    return set_find(v, a) == set_find(v, b);
}

struct v
{
    double x;
    double y;
};

struct edge
{
    int a;
    int b;
    double w;
    edge() : a(0), b(0), w(0) {}
    edge(int _a, int _b, double _w) : a(_a), b(_b), w(_w)
    {}
};

double tree_distance(int a, int b, vector<v>& vertices)
{
    double x1 = vertices[a].x;
    double y1 = vertices[a].y;
    double x2 = vertices[b].x;
    double y2 = vertices[b].y;
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

bool comp(edge& a, edge& b)
{
    return a.w < b.w;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, e, p;
    cin >> n >> e >> p;
    vector<v> vertices(n + 1);
    vector<int> key(n + 1);
    vector<int> parent(n + 1), rank(n + 1, 0);
    vector<edge> edges;
    edges.reserve(n * (n - 1) / 2);
    double cost = 0;
    for (int i = 0; i < n; ++i)
    {
        cin >> vertices[i + 1].x >> vertices[i + 1].y;
        if (i + 1 <= e)
        {
            parent[i + 1] = 1;
            rank[1] += 1;
        }
        else
        {
            parent[i + 1] = i + 1;
            rank[i + 1] = 0;
        }
    }
    for (int i = 0; i < p; ++i)
    {
        int a, b;
        cin >> a >> b;
        set_union(parent, rank, a, b);
    }
    for (int i = 1; i < n + 1; ++i)
    {
        for (int j = i + 1; j < n + 1; ++j)
        {
            edges.emplace_back(i, j, tree_distance(i, j, vertices));
            // cout << "edges i: " << i << " | j: " << j << " | distance: " << tree_distance(i, j, vertices) << "\n";
        }
    }
    sort(edges.begin(), edges.end(), comp);
    for (auto &ed : edges)
    {
        int a = ed.a;
        int b = ed.b;
        if (set_find(parent, a) != set_find(parent, b))
        {
            set_union(parent, rank, a, b);
            // cout << "union: " << ed.a << " and " << ed.b << " | w: " << ed.w << "\n";
            cost += ed.w;
        }
    }
    cout << cost << "\n";
    return 0;
}
