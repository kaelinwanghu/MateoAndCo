#include <bits/stdc++.h>
using namespace std;

class unionfind {
    public:
        vector<int32_t> parent;
        vector<int32_t> rank;
        unionfind(int n){
            parent = vector<int32_t>(n);
            rank = vector<int32_t>(n);
            for(int i = 0; i < n; i++){
                parent[i] = i;
                rank[i] = 0;
            }
        }

        int32_t set_find(int32_t a)
        {
            deque<int32_t> d;
            int32_t front;
            while (parent[a] != a)
            {
                d.emplace_front(a);
                a = parent[a];
            }

            while (!d.empty())
            {
                front = d.front();
                d.pop_front();
                parent[front] = a;
            }
            return a;
        }

        void set_union(const int32_t a, const int32_t b)
        {
            int32_t a_root = set_find(a);
            int32_t b_root = set_find(b);
            if (a_root != b_root)
            {
                if (rank[a_root] > rank[b_root])
                {
                    parent[b_root] = a_root;
                }
                else if (rank[a_root] == rank[b_root])
                {
                    rank[a_root]++;
                    parent[b_root] = a_root;
                }
                else
                {
                    parent[a_root] = b_root;
                }
            }
        }

        bool set_query(const int32_t a, const int32_t b)
        {
            return set_find(a) == set_find(b);
        }
};


int main() // example usage
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    unionfind uf(n);
    for(int i = 0; i < q; i++){
        char op;
        int a,b;
        cin >> op >> a >> b;
        if(op=='?'){
            if(uf.set_query(a, b)) { // a and b in same set?
                cout << "yes\n";
            } else {
                cout << "no\n";
            }
        } else {
            uf.set_union(a, b); // union a and b sets
        }
    }
    
    return 0;
}