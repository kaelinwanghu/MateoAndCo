#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    int max_possible = n + q;
    vector<int> parent(max_possible);
    vector<int> ruler(max_possible);
    vector<bool> balkanized(max_possible);
    vector<int> area_node(n + 1);

    int node_id = n;

    for (int i = 1; i <= n; ++i)
    {
        parent[i] = i;
        ruler[i] = i;
        balkanized[i] = false;
        area_node[i] = i;
    }

    auto find_root = [&](int x)
    {
        while (parent[x] != x)
        {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    };

    function<int(int)> get_node = [&](int area) -> int
    {
        int node = area_node[area];
        int root = find_root(node);
        if (balkanized[root])
        {
            int ind = ++node_id;
            parent[ind] = ind;
            ruler[ind] = area;
            balkanized[ind] = false;
            area_node[area] = ind;
            return ind;
        }
        else
        {
            parent[node] = root;
            area_node[area] = root;
            return root;
        }
    };

    for (int i = 0; i < q; ++i)
    {
        char op;
        cin >> op;
        if (op == 'a')
        {
            int x, y;
            cin >> x >> y;
            int root = get_node(x);
            int ry = get_node(y);
            if (root != ry)
            {
                parent[ry] = root;
            }
        }
        else if (op == 'b')
        {
            int x;
            cin >> x;
            int root = get_node(x);
            balkanized[root] = true;
        }
        else if (op == 'c')
        {
            int x;
            cin >> x;
            int root = get_node(x);
            cout << ruler[root] << '\n';
        }
    }

    return 0;
}
