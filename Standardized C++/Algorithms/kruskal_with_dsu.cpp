#include <bits/stdc++.h>
using namespace std;

// from https://cp-algorithms.com/graph/mst_kruskal_with_dsu.html

struct edge {
    int u, v, weight;
    bool operator<(edge const& other){
        return weight < other.weight;
    }
};

void make_set(int v, vector<int>& parent, vector<int>& rank){
    parent[v] = v;
    rank[v] = 0;
}

int find_set(int v, vector<int>& parent){
    if(v == parent[v]){
        return v;
    } else {
        return parent[v] = find_set(parent[v], parent); // flatten tree during search
    }
}

void union_sets(int a, int b, vector<int>& parent, vector<int>& rank){
    a = find_set(a, parent);
    b = find_set(b, parent);
    if(a != b){
        if(rank[a] < rank[b]){
            swap(a,b);
        }
        parent[b] = a;
        if(rank[a] == rank[b]){
            rank[a]++;
        }
    }
}

vector<edge> kruskals(vector<edge> edges, int n){
    vector<int> parent, rank; // disjoint set union
    int cost = 0;
    vector<edge> result;
    parent.resize(n);
    rank.resize(n);
    for(int i = 0; i < n; i++) make_set(i, parent, rank);

    sort(edges.begin(), edges.end());

    for(edge e : edges){
        if(find_set(e.u, parent) != find_set(e.v, parent)){
            cost += e.weight;
            result.emplace_back(e);
            union_sets(e.u, e.v, parent, rank);
        }
    }

    return result;
}

int main(){
    int n;
    vector<edge> edges;

    // process inputs

    vector<edge> result = kruskals(edges, n);

}