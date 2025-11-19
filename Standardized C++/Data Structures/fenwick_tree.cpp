#include <bits/stdc++.h>
using namespace std;

struct fenwick_tree
{
    int32_t n = 0;
    vector<int64_t> bit; // bit[1..n]

    fenwick_tree() = default;
    explicit fenwick_tree(int32_t n_) { init(n_); }

    void init(int32_t n_)
    {
        n = n_;
        bit.assign(n + 1, 0);
    }

    // build from 0-indexed array a[0..n-1]
    void build_from(const vector<int64_t>& a)
    {
        init(static_cast<int32_t>(a.size()));
        for (int32_t i = 0; i < n; ++i) add(i + 1, a[i]);
    }

    // add delta to index idx (1-indexed)
    void add(int32_t idx, int64_t delta)
    {
        for (; idx <= n; idx += idx & -idx) bit[idx] += delta;
    }

    // prefix sum [1..idx]
    int64_t prefix_sum(int32_t idx) const
    {
        int64_t res = 0;
        for (; idx > 0; idx -= idx & -idx) res += bit[idx];
        return res;
    }

    // range sum [l..r] with 1-indexing
    int64_t range_sum(int32_t l, int32_t r) const
    {
        if (l > r) return 0;
        return prefix_sum(r) - prefix_sum(l - 1);
    }
};