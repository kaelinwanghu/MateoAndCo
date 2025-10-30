#include <bits/stdc++.h>
using namespace std;

// from https://cp-algorithms.com/graph/mst_kruskal.html
// This version has poor runtime compared to disjoint-set

struct edge {
    int u, v, weight;
    bool operator<(edge const& other) {
        return weight < other.weight;
    }
};

vector<edge> get_mst(vector<edge> edges, int n){
    int mst_cost = 0;
    vector<int> tree_id(n);
    vector<edge> result; // mst

    for(int i = 0; i < n; i++) tree_id[i] = i; // shitty disjoint set 

    // actual algo begins here
    sort(edges.begin(), edges.end()); 

    for(edge e : edges){
        if(tree_id[e.u] != tree_id[e.v]){ // if lowest edge is not in mst, add it
            mst_cost += e.weight;
            result.push_back(e);

            int old_id = tree_id[e.u], new_id = tree_id[e.v]; // set new id
            for(int i = 0; i < n; i++){ // set new id for other parts of tree
                if(tree_id[i] == old_id) tree_id[i] = new_id; 
            }
        }
    }

    return result;
}

int main(){
    int n;
    vector<edge> edges;
    // do input processing to populate n + edges

    vector<edge> result = get_mst(edges, n);
    
    // result should now be in result vector, do whatever

    
}